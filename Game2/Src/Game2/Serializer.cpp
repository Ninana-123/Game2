#include "pch.h"
#include "Serializer.h"

namespace Engine
{
    bool Engine::Serializer::parseJsonFilesInDirectory(const std::string& directoryPath, std::vector<rapidjson::Value>& jsonObjects)
    {
        try
        {
            // Iterate through files in the specified directory
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
            {
                // Check if the file is a regular file and has a .json extension
                if (entry.is_regular_file() && entry.path().extension() == ".json")
                {
                    // Open the JSON file
                    std::ifstream file(entry.path());
                    if (!file.is_open())
                    {
                        std::cerr << "Failed to open file: " << entry.path() << std::endl;
                        continue;
                    }

                    // Read the content of the JSON file into a string
                    std::string jsonContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                    // Parse the string into a rapidjson document
                    rapidjson::Document doc;
                    doc.Parse(jsonContent.c_str());

                    if (doc.HasParseError())
                    {
                        std::cerr << "JSON parse error in file: " << entry.path() << std::endl;
                        continue;
                    }

                    // Store the parsed JSON object in the vector
                    jsonObjects.push_back(doc);
                }
            }

            return true; // Parsing successful
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Exception: " << ex.what() << std::endl;
            return false; // Parsing failed
        }
    }

    /*
    Entity Serializer::DeserializeEntity(const rapidjson::Value& jsonEntity)
    {
        //Read json contents
        //create entity using EntityManager
        // if word "transform"
        //create transform component from component factory
        // assign json contents to transform data members
        return;
    }
    */

   
}





