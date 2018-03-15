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
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA */

#include <mysql/components/component_implementation.h>
#include <mysql/components/service_implementation.h>
#include <mysql/components/services/component_sys_var_service.h>
#include "../../components/mysql_server/component_sys_var_service.h"
#include <fcntl.h>
#include <mysql/plugin.h>
#include <typelib.h>
#include <my_macros.h>

#define MAX_BUFFER_LENGTH 100
int log_text_len= 0;
char log_text[MAX_BUFFER_LENGTH];
FILE *outfile;
const char *filename= "test_component_sys_var_service_int.log";

#define WRITE_LOG(format,lit_log_text) \
  log_text_len= sprintf(log_text, format, lit_log_text); \
  fwrite((uchar*)log_text, sizeof(char), log_text_len, outfile)

REQUIRES_SERVICE_PLACEHOLDER(component_sys_variable_register);
REQUIRES_SERVICE_PLACEHOLDER(component_sys_variable_unregister);

static int int_variable_value;
static int int_var_2_value;
static int uint_variable_value;

/**
  Initialization entry method for test component. It executes the tests of
  the service.
*/
static mysql_service_status_t test_component_sys_var_service_int_init()
{
  unlink(filename);
  outfile= fopen(filename, "w+");

  WRITE_LOG("%s\n", "test_component_sys_var_int init:");

  INTEGRAL_CHECK_ARG(int) int_arg, int_arg_2;

  int_arg.def_val= 8;
  int_arg.min_val= 0;
  int_arg.max_val= 1024;
  int_arg.blk_sz= 0;
  if (mysql_service_component_sys_variable_register->register_variable(
                 "test_component_int", "int_sys_var", PLUGIN_VAR_INT,
                 "Registering int sys_variable",
                 NULL, NULL, (void *) &int_arg,
                 (void *) &int_variable_value))
  {
    WRITE_LOG ("%s\n", "int register_variable failed.");
  }

  int_arg_2.def_val= 1024;
  int_arg_2.min_val= 11;
  int_arg_2.max_val= 2048;
  int_arg_2.blk_sz= 0;
  if (mysql_service_component_sys_variable_register->register_variable(
                 "test_component_int", "int_sys_var_2",
                 PLUGIN_VAR_INT,
                 "Registering int sys_variable",
                 NULL, NULL, (void *) &int_arg_2,
                 (void *) &int_var_2_value))
  {
    WRITE_LOG ("%s\n", "uint register_variable failed.");
  }

  INTEGRAL_CHECK_ARG(uint) uint_arg;
  uint_arg.def_val= 1024;
  uint_arg.min_val= 10;
  uint_arg.max_val= 10241024;
  uint_arg.blk_sz= 0;
  if (mysql_service_component_sys_variable_register->register_variable(
                 "test_component_int", "uint_sys_var",
                 PLUGIN_VAR_INT | PLUGIN_VAR_UNSIGNED,
                 "Registering uint sys_variable",
                 NULL, NULL, (void *) &uint_arg,
                 (void *) &uint_variable_value))
  {
    WRITE_LOG ("%s\n", "uint register_variable failed.");
  }

  WRITE_LOG("%s\n", "test_component_sys_var_int end of init:");
  fclose(outfile);

  return false;
}

/**
  De-initialization method for Component.
*/
static mysql_service_status_t test_component_sys_var_service_int_deinit()
{
  char *var_value;
  size_t len= 0;

  outfile= fopen(filename, "a+");
  WRITE_LOG("%s\n", "test_component_sys_var_int deinit:");

  var_value= new char[1024];

  if (mysql_service_component_sys_variable_register->get_variable(
                                "test_component_int", "int_sys_var",
                                (void **) &var_value, &len))
  {
    WRITE_LOG ("%s\n", "get_variable failed.");
  }
  else
  {
    WRITE_LOG ("variable value : %s\n", var_value);
  }

  if (mysql_service_component_sys_variable_register->get_variable(
                                "test_component_int", "uint_sys_var",
                                (void **) &var_value, &len))
  {
    WRITE_LOG ("%s\n", "get_variable failed.");
  }
  else
  {
    WRITE_LOG ("variable value : %s\n", var_value);
  }

  if (mysql_service_component_sys_variable_register->get_variable(
                                "test_component_int", "int_sys_var_2",
                                (void **) &var_value, &len))
  {
    WRITE_LOG ("%s\n", "get_variable failed.");
  }
  else
  {
    WRITE_LOG ("variable value : %s\n", var_value);
  }

  if (mysql_service_component_sys_variable_unregister->unregister_variable(
                    "test_component_int", "int_sys_var"))
  {
    WRITE_LOG ("%s\n", "int unregister_variable failed.");
  }

  if (mysql_service_component_sys_variable_unregister->unregister_variable(
                    "test_component_int", "uint_sys_var"))
  {
    WRITE_LOG ("%s\n", "unsigned int unregister_variable failed.");
  }

  if (mysql_service_component_sys_variable_unregister->unregister_variable(
                    "test_component_int", "int_sys_var_2"))
  {
    WRITE_LOG ("%s\n", "int unregister_variable failed.");
  }

  if (mysql_service_component_sys_variable_register->get_variable(
                                "test_component_int", "int_sys_var_2",
                                (void **) &var_value, &len))
  {
    WRITE_LOG ("%s\n", "get_variable failed.");
  }
  else
  {
    WRITE_LOG ("variable value : %s\n", var_value);
  }

  WRITE_LOG("%s\n", "test_component_sys_var_int end of deinit:");

  delete []var_value;
  fclose(outfile);
  return false;
}

/* An empty list as no service is provided. */
BEGIN_COMPONENT_PROVIDES(test_component_sys_var_service)
END_COMPONENT_PROVIDES()

/* A list of required services. */
BEGIN_COMPONENT_REQUIRES(test_component_sys_var_service)
  REQUIRES_SERVICE(component_sys_variable_register)
  REQUIRES_SERVICE(component_sys_variable_unregister)
END_COMPONENT_REQUIRES()

/* A list of metadata to describe the Component. */
BEGIN_COMPONENT_METADATA(test_component_sys_var_service)
  METADATA("mysql.author", "Oracle Corporation")
  METADATA("mysql.license", "GPL")
  METADATA("test_component_sys_var_service", "1")
END_COMPONENT_METADATA()

/* Declaration of the Component. */
DECLARE_COMPONENT(test_component_sys_var_service, "mysql:test_component_sys_var_service")
  test_component_sys_var_service_int_init,
  test_component_sys_var_service_int_deinit
END_DECLARE_COMPONENT()

/* Defines list of Components contained in this library. Note that for now we
  assume that library will have exactly one Component. */
DECLARE_LIBRARY_COMPONENTS
  &COMPONENT_REF(test_component_sys_var_service)
END_DECLARE_LIBRARY_COMPONENTS
