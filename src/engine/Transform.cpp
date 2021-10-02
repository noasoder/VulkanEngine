#include "Transform.h"

#include "Utility/Types.h"


Transform::Transform(const Vec3& pos, const glm::quat& rot, const Vec3& scale)
{
    m_pos = pos;
    m_rot = rot;
    m_scale = scale;
}

glm::mat4 Transform::GetMatrix()
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0), m_pos);
    glm::mat4 rotate = glm::mat4_cast(m_rot);
    glm::mat4 scale = glm::scale(glm::mat4(1.0), m_scale);

    return translate * rotate * scale;
}

Vec3 Transform::GetAt()
{
    return Vec3(GetMatrix()[1].x, GetMatrix()[1].y, GetMatrix()[1].z);
}

Vec3 Transform::GetUp()
{
    return Vec3(GetMatrix()[2].x, GetMatrix()[2].y, GetMatrix()[2].z);
}

void Transform::RotateLocal(const double& xx, const double& yy, const double& zz, const double& a)
{
    Vec3 in = Vec3(xx, yy, zz);
    if (in != Vec3(0))
    {
        glm::quat rot = glm::angleAxis(glm::radians((float)a), glm::normalize(in));
        m_rot = m_rot * rot;
    }
}

void Transform::RotateWorld(const double& xx, const double& yy, const double& zz, const double& a)
{
    Vec3 in = Vec3(xx, yy, zz);
    if (in != Vec3(0))
    {
        glm::quat rot = glm::angleAxis(glm::radians((float)a), glm::normalize(in));
        m_rot = rot * m_rot;
    }
}

void Transform::TranslateWorld(Vec3 move)
{
    m_pos += move;
}

void Transform::TranslateLocal(Vec3 move)
{
    glm::mat4 mat = glm::translate(GetMatrix(), move);
    m_pos = mat[3];
}

// glm::quat Transform::RotateTowards(glm::quat q2, float maxAngle) {

//     if (maxAngle < 0.001f) {
//         // No rotation allowed. Prevent dividing by 0 later.
//         return m_rot;
//     }

//     float cosTheta = dot(m_rot, q2);

//     // q1 and q2 are already equal.
//     // Force q2 just to be sure
//     if (cosTheta > 0.9999f) {
//         m_rot = q2;
//         return q2;
//     }

//     // Avoid taking the long path around the sphere
//     if (cosTheta < 0) {
//         m_rot = m_rot * -1.0f;
//         cosTheta *= -1.0f;
//     }

//     float angle = acos(cosTheta);

//     // If there is only a 2&deg; difference, and we are allowed 5&deg;,
//     // then we arrived.
//     if (angle < maxAngle) {
//         m_rot = q2;
//         return q2;
//     }

//     float fT = maxAngle / angle;
//     angle = maxAngle;

//     glm::quat res = (sin((1.0f - fT) * angle) * m_rot + sin(fT * angle) * q2) / sin(angle);
//     m_rot = glm::normalize(res);
//     return m_rot;
// }