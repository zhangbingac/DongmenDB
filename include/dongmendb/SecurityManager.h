//
// Created by Sam on 2018/1/26.
//

#ifndef DONGMENDB_SECURITYMANAGER_H
#define DONGMENDB_SECURITYMANAGER_H
/**
 * 安全管理
 * 安全性管理：用户，对象，权限
 * 数据保存在元数据表user,role, userrole, userright, roleright中。
 *
 */

#include "DongmenDB.h"

#include <vector>

using namespace std;

typedef enum{
    RIGHT_SELECT = 0,
    RIGHT_INSERT,
    RIGHT_UPDATE,
    RIGHT_DELETE,
    RIGHT_ALL
}right_type;


class Right {
public:
    char *objectName;
    right_type rightType;
};

class Role {
public:
    char *roleName;
    vector<Role*> *roles;
    vector<Right*> *rights;
};

class User{
public:
    char *userName;
    char *password;
    vector<Role*> *roles;
    vector<Right*> *rights; // error: template argument 1 is invalid
};

class SecurityManager {
public:
/**
 * 在系统表user中增加用户
 *  在 exp_04_02_rights_manager.c 实现
 * @param userName
 * @param roles
 * @param rights
 * @return
 */
    int security_manager_create_user(const char *userName);

/**
 * 在系统表role中增加角色
 *  在 exp_04_02_rights_manager.c 实现
 * @param roleName
 * @param roles
 * @param rights
 * @return
 */
    int security_manager_create_role(const char *roleName);

/**
 * 给用户授予角色。在系统表userrole中增加
 * @param securityManager
 * @param userName
 * @param roleName
 * @return
 */
    int security_manager_grant_role_to_user(const char *userName, const char *roleName);

/**
 * 给用户授予权限。在系统表userright中增加
 * @param securityManager
 * @param userName
 * @param objName
 * @param rightType
 * @return
 */
    int security_manager_grant_right_to_user(const char *userName, const char *objName, right_type rightType);

/**
 * 给角色授予权限。在系统表roleright中增加
 * @param securityManager
 * @param roleName
 * @param objName
 * @param rightType
 * @return
 */
    int security_manager_grant_right_to_role(const char *roleName, const char *objName, right_type rightType);

/**
 * 收回用户的角色。
 * @param securityManager
 * @param userName
 * @param roleName
 * @return
 */
    int security_manager_revoke_role_from_user(const char *userName, const char *roleName);

/**
 * 收回用户的权限
 * @param securityManager
 * @param userName
 * @param objName
 * @param rightType
 * @return
 */
    int security_manager_revoke_right_from_user(const char *userName, const char *objName, right_type rightType);

/**
 * 收回角色的权限
 * @param securityManager
 * @param roleName
 * @param objName
 * @param rightType
 * @return
 */
    int security_manager_revoke_right_from_role(const char *roleName, const char *objName, right_type rightType);

/**
 *  在 exp_04_02_rights_manager.c 中实现
 * @param userName
 * @param objName
 * @param rightType
 * @return 有授权返回1，无授权返回0
 */
    int security_manager_check_right(const char *userName, const char *objName, right_type rightType);

/**
 * 在 securitymanager.c 中实现
 * @param userName
 * @return
 */
    User *security_manager_get_user(const char *userName);

/**
 * 在 securitymanager.c 实现
 * @param roleName
 * @return
 */
    Role *security_manager_get_role(const char *roleName);

/**
 * 初始化用于安全管理的系统数据表.
 * 在 securitymanager.c 中实现
 * @param db
 * @return
 */
    int security_manager_init(SecurityManager *securityManager);


} ;


#endif //DONGMENDB_SECURITYMANAGER_H
