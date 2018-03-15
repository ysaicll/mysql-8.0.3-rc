/* Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02111-1307  USA */

#ifndef COMPONENT_STAUTS_VARIABLE_SERVICE_H
#define COMPONENT_STAUTS_VARIABLE_SERVICE_H

#include <mysql/status_var.h>
#include <mysql/components/services/component_status_var_service.h>
#include <mysql/components/service_implementation.h>

extern int add_status_vars(const st_mysql_show_var *);
extern void remove_status_vars(st_mysql_show_var *);

/**
  An implementation of the component status variables Service to register
  variable and unregister variable.
*/
class mysql_status_variable_registration_imp
{
public:
  /**
    Register status variable.

    @param  status_var fully constructed status variable object.
    @return Status of performed operation
    @retval false success
    @retval true failure

    Note: Please see the components/test/test_status_var_service.cc file,
    to know how to construct status varables for different variable types.
  */
  static DEFINE_BOOL_METHOD(register_variable,
  (STATUS_VAR *status_var));

  /**
    Unregister's status variable.
    @param  status_var STATUS_VAR object with only the name of the variable,
                       which has to be removed from the global list.
    @return Status of performed operation
    @retval false success
    @retval true failure
  */
  static DEFINE_BOOL_METHOD(unregister_variable,
  (STATUS_VAR *status_var));
};
#endif /* COMPONENT_STATUS_VARIABLE_SERVICE_H */