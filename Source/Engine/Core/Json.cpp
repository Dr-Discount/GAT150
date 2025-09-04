#include "Json.h"
#include "File.h"
#include "Logger.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace viper::json {
    bool Load(const std::string& filename, document_t& document) {
        // read the file into a string
        std::string buffer;
        if (!ReadTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}.", filename);
            return false;
        }
        
		//Logger::Info("JSON: {}", buffer);

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        document.ParseStream(istream);
     
        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}.", filename);
            return false;
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, int& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            if (required) Logger::Error("Could not read Json value (int): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();
		Logger::Info("Read Json value (int): {} = {}.", name, data);

        return true;
    }

    bool Read(const value_t& value, const std::string& name, float& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber()) {
            if (required) Logger::Error("Could not read Json value (float): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetFloat();
		Logger::Info("Read Json value (float): {} = {}.", name, data);

        return true;
    }

    bool Read(const value_t& value, const std::string& name, bool& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
            if (required) Logger::Error("Could not read Json value (bool): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetBool();
		Logger::Info("Read Json value (bool): {} = {}.", name, data);

        return true;
    }

    bool Read(const value_t& value, const std::string& name, std::string& data, bool required) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            if (required) Logger::Error("Could not read Json value (string): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetString();
		Logger::Info("Read Json value (string): {} = {}.", name, data);

        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec2& data, bool required) {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
            if (required) Logger::Error("Could not read Json value (vec2): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

		Logger::Info("Read Json value (vec2): {} = ({}, {}).", name, data.x, data.y);
        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec3& data, bool required) {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3) {
            if (required) Logger::Error("Could not read Json value (vec3): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
}