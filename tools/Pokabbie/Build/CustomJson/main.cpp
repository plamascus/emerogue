#include "main.h"

#include <functional>
#include <unordered_map>

typedef std::function<void(std::ofstream&, json const&)> ExporterFunc;

static std::string readTextFile(std::string const& filepath) 
{
    std::ifstream fileStream(filepath);

    if (!fileStream.is_open())
        FATAL_ERROR("Cannot open file %s for reading.\n", filepath.c_str());

    std::string text;

    fileStream.seekg(0, std::ios::end);
    text.resize(fileStream.tellg());

    fileStream.seekg(0, std::ios::beg);
    fileStream.read(&text[0], text.size());

    fileStream.close();

    return text;
}

void ExportTrainerData_C(std::ofstream& fileStream, json const& jsonData);
void ExportTrainerData_Pory(std::ofstream& fileStream, json const& jsonData);
void ExportBattleMusicData_C(std::ofstream& fileStream, json const& jsonData);

static std::map<std::string, ExporterFunc> CreateExportMap()
{
    std::map<std::string, ExporterFunc> mapping;

    mapping["trainers_c"] = ExportTrainerData_C;
    mapping["trainers_pory"] = ExportTrainerData_Pory;
    mapping["battle_music_c"] = ExportBattleMusicData_C;

    return mapping;
}

int main(int argc, char* argv[]) 
{
    std::string inputArgs = "customjson ";
    for (int i = 1; i < argc; ++i)
    {
        inputArgs += " ";
        inputArgs += argv[i];
    }
    LOG_MSG("%s", inputArgs.c_str());

    if (argc != 4)
        FATAL_ERROR("USAGE: mapjson <exporter> <input path> <output path>\n");

    std::map<std::string, ExporterFunc> validExporters = CreateExportMap();

    std::string exporter(argv[1]);
    std::string sourceFilePath(argv[2]);
    std::string exportFilePath(argv[3]);

    auto exporterIt = validExporters.find(exporter);

    if (exporterIt == validExporters.end())
    {
        FATAL_ERROR("Invalid exporter.\nUSAGE: mapjson <exporter> <input path> <output path>\n");
    }

    json jsonData;

    try
    {
        jsonData = json::parse(readTextFile(sourceFilePath));
    }
    catch (json::exception const& e)
    {
        FATAL_ERROR("Json Error: %s\n", e.what());
    }

    std::ofstream writeStream(exportFilePath, std::ofstream::binary);
    if (!writeStream.is_open())
    {
        FATAL_ERROR("Cannot open file %s for writing.\n", exportFilePath.c_str());
    }

    writeStream << "//\n";
    writeStream << "// DO NOT EDIT THIS FILE\n";
    writeStream << "// This file was generated using Pokabbie\\CustomJson from '" << sourceFilePath << "'\n";
    writeStream << "//\n";
    writeStream << "\n";

    // Run the exporter
    exporterIt->second(writeStream, jsonData);

    writeStream.close();

    return 0;
}

void FatalExit()
{
    std::exit(1);
}