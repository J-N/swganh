// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#ifndef WIN32
#include <Python.h>
#endif

#include <string>
#include <memory>

#include <boost/python.hpp>

namespace swganh {
namespace scripting {

    class PythonScript
    {
    public:
        PythonScript(const std::string& filename);

        void Run();

        template<typename T>
        void SetContext(const std::string& key, T value)
        {
	        try{
				globals_[key.c_str()] = value;
            } 
            catch (boost::python::error_already_set &) 
            {
                GetPythonException();
            }   
        }
		void SetImport(const std::string& import)
		{
			imports_ = import;
		}

        boost::python::object GetGlobals() { return globals_; }

		boost::python::object GetFileObject() { return file_object_; }
    private:
        PythonScript();

        void GetPythonException();

        void ReadFileContents();

        std::string filename_;
        std::string filecontents_;
		std::string imports_;
        boost::python::object file_object_;
        boost::python::object globals_;
    };

}}  // namespace swganh::scripting
