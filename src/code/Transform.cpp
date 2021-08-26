#include "Transform.h"

#include "Utility/Types.h"


Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale)
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

glm::vec3 Transform::GetAt()
{
    return glm::vec3(GetMatrix()[1].x, GetMatrix()[1].y, GetMatrix()[1].z);
}

glm::vec3 Transform::GetUp()
{
    return glm::vec3(GetMatrix()[2].x, GetMatrix()[2].y, GetMatrix()[2].z);
}

glm::quat Transform::CreateFromAxisAngle(const double& xx, const double& yy, const double& zz, const double& a)
{
    // Here we calculate the sin( theta / 2) once for optimization
    double factor = sin(a / 2.0);

    // Calculate the x, y and z of the quaternion
    double x = xx * factor;
    double y = yy * factor;
    double z = zz * factor;

    // Calcualte the w value by cos( theta / 2 )
    double w = cos(a / 2.0);

    return glm::normalize(glm::quat(x, y, z, w));
}

void Transform::Rotate(const double& xx, const double& yy, const double& zz, const double& a)
{
    m_rot = m_rot * CreateFromAxisAngle(xx, yy, zz, a);
}

void QuaternionRotate(const glm::vec3& axis, float angle)
{
    float angleRad = glm::radians(angle);
    auto& axisNorm = glm::normalize(axis);

    float w = glm::cos(angleRad / 2);
    float v = glm::sin(angleRad / 2);
    glm::vec3 qv = axisNorm * v;

    glm::quat quaternion(w, qv);
    glm::mat4 quatTransform = glm::mat4_cast(quaternion);

    // Now with the quaternion transform you rotate any vector or compound it with another transformation matrix
}