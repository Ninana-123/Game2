#pragma once
#include "pch.h"
#include "Entity.h"
#include "Prefab.h"
#include "EntityManager.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace Engine
{
    class Serializer
    {
    public:
        // Function to parse JSON files in a directory and store them in a vector of JSON objects
        static bool parseJsonFilesInDirectory(const std::string& directoryPath, std::vector<rapidjson::Value>& jsonObjects);

        // deserialize entity
        //Entity DeserializeEntity(const rapidjson::Value& jsonEntity);

        // deserialize prefabs
       // Prefab DeserializePrefab(const std::string& filePath);

        //USAGE
        /*
        // Specify the directory path containing JSON files
        std::string directoryPath = "path/to/your/directory";

        // Create a vector to store parsed JSON objects
        std::vector<rapidjson::Value> jsonObjects;

        // Use the Serializer class to parse JSON files in the directory
        Engine::Serializer::parseJsonFilesInDirectory(directoryPath, jsonObjects))
        
        // Parsing successful, now you have a vector of parsed JSON objects
        for (const auto& jsonObject : jsonObjects)
        {
             // Call DeserializeEntity(jsonObject)
        }
        

        */
    };
}