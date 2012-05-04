// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include <boost/python/module.hpp>

#include "command_binding.h"

BOOST_PYTHON_MODULE(py_command)
{
    swganh::command::ExportCommand();
}
