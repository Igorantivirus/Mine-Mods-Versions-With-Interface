#pragma once

#include<string>
#include<fstream>
#include<filesystem>

#include<iostream>

#include"PathMeneger.hpp"

struct VersionInfo
{
	std::string name;
	std::string version;
};

class ProgrammPathMeneger
{
public:
	ProgrammPathMeneger() :
		minePath{ InitMinecraftPath() }
	{
		if (!existsMain())
			createAllFiles();


		std::ifstream in{ minePath + CUR_VERS_FILE };
		std::getline(in, currentName);		//Считывание имени текущей версии
		std::getline(in, currentVersion);	//Считывание версии майнкрафта
		in.close();


		versionNames = meneger.getPathFrom(minePath + VERSIONS_PATH);
	}

	const std::string& getCurrentName() const
	{
		return currentName;
	}
	const std::string& getCurrentVersion() const
	{
		return currentVersion;
	}

	const std::vector<std::string> getVersionNames() const
	{
		return versionNames;
	}
	VersionInfo getVersionAtIndex(const unsigned int ind) const
	{
		if (ind >= versionNames.size())
			return {};
		std::ifstream in{ minePath + VERSIONS_PATH + versionNames[ind] + '\\' + VERS_INF_FILE};
		VersionInfo res;
		std::getline(in, res.name);
		std::getline(in, res.version);
		return res;
	}

	std::vector<std::string> getMinecraftVersions() const
	{
		return meneger.getPathFrom(minePath + MINE_VERSIONS_PATH);
	}

	void clearPaths()
	{
		meneger.clearPath(minePath + MINE_MODS_PATH);
		meneger.clearPath(minePath + MINE_CONFIG_PATH);

		setNewCurrentVersion(NONE_INFO, NONE_INFO);
	}

	void clearCurrent()
	{
		const std::string fName = minePath + VERSIONS_PATH + currentName + '\\';

		meneger.clearPath(fName + MINE_MODS_PATH);
		meneger.clearPath(fName + MINE_CONFIG_PATH);
	}

	void deleteVersionAtIndex(const unsigned int ind)
	{
		if (ind >= versionNames.size())
			return;

		if (currentName == versionNames[ind])
			clearPaths();

		meneger.deletePath(minePath + VERSIONS_PATH + versionNames[ind] + '\\');

		versionNames.erase(versionNames.begin() + ind);
	}

	void createVersion(const std::string& name, const std::string& version)
	{
		const std::string fName = minePath + VERSIONS_PATH + name + '\\';
		meneger.makePathIn(fName);
		meneger.makePathIn(fName + MINE_MODS_PATH);
		meneger.makePathIn(fName + MINE_CONFIG_PATH);

		meneger.makeFileWithText(fName + VERS_INF_FILE, name + '\n' + version);
		
		meneger.copyAll(minePath + MINE_MODS_PATH, fName + MINE_MODS_PATH);
		meneger.copyAll(minePath + MINE_CONFIG_PATH, fName + MINE_CONFIG_PATH);

		versionNames.push_back(name);
		setNewCurrentVersion(name, version);
	}

	bool haveVersionName(const std::string& name) const
	{
		for (const auto& i : versionNames)
			if (i == name)
				return true;
		return false;
	}

	void updateCurrent()
	{
		const std::string fName = minePath + VERSIONS_PATH + currentName + '\\';

		meneger.clearPath(fName + MINE_MODS_PATH);
		meneger.clearPath(fName + MINE_CONFIG_PATH);

		meneger.copyAll(minePath + MINE_MODS_PATH, fName + MINE_MODS_PATH);
		meneger.copyAll(minePath + MINE_CONFIG_PATH, fName + MINE_CONFIG_PATH);
	}

	void setVersionAt(const unsigned int ind)
	{
		if (ind >= versionNames.size())
			return;
		clearPaths();

		std::string fName = minePath + VERSIONS_PATH + versionNames[ind] + '\\';

		std::ifstream in{ fName + VERS_INF_FILE };
		std::getline(in, currentName);
		std::getline(in, currentVersion);
		in.close();

		meneger.makeFileWithText(minePath + CUR_VERS_FILE, currentName + '\n' + currentVersion);

		meneger.copyAll(fName + MINE_MODS_PATH, minePath + MINE_MODS_PATH);
		meneger.copyAll(fName + MINE_CONFIG_PATH, minePath + MINE_CONFIG_PATH);
	}

private:

	std::string currentName;
	std::string currentVersion;

	std::vector<std::string> versionNames;

	const std::string minePath;
	
	PathMeneger meneger;

private:

	void setNewCurrentVersion(const std::string& name, const std::string& vers)
	{
		meneger.makeFileWithText(minePath + CUR_VERS_FILE, name + '\n' + vers);

		currentName = name;
		currentVersion = vers;
	}

	void createAllFiles()
	{
		meneger.makePathIn(minePath + MAIN_PATH);
		meneger.makePathIn(minePath + VERSIONS_PATH);
		meneger.makeFileWithText(minePath + CUR_VERS_FILE, "None\nNone");
	}

	bool existsMain() const
	{
		return fs::exists(minePath + CUR_VERS_FILE);
	}

private:

	static std::string InitMinecraftPath()
	{
		char* appdata = nullptr;
		size_t len = 0;

		errno_t err = _dupenv_s(&appdata, &len, "APPDATA");

		if (err != 0 || appdata == nullptr)
			return "";

		std::string fName = appdata;
		fName += "\\.minecraft\\";

		free(appdata);
		return fName;
	}

};