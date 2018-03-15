/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

// MySQL DB access module, for use by plugins and others
// For the module that implements interactive DB functionality see mod_db

#ifndef X_CLIENT_XPROTOCOL_QUERY_INSTANCES_H_
#define X_CLIENT_XPROTOCOL_QUERY_INSTANCES_H_

#include <memory>


namespace xcl {

class Query_instances {
 public:
  using Instance_id = uint64_t;

 public:
  virtual ~Query_instances() {
  }

  virtual Instance_id instances_fetch_begin() = 0;
  virtual void instances_fetch_end() = 0;
  virtual bool is_instance_active(const Instance_id id) = 0;
};

}  // namespace xcl

#endif  // X_CLIENT_XPROTOCOL_QUERY_INSTANCES_H_
