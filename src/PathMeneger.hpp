#pragma once

#include<string>
#include<fstream>
#include<filesystem>
#include<vector>

#include"Names.hpp"

class PathMeneger
{
public:

	void clearPath(const std::string& path) const
	{
		if (!fs::is_directory(path))
			return;
		fs::remove_all(path);
		fs::create_directory(path);
	}

	void deletePath(const std::string& path) const
	{
		if (!fs::is_directory(path))
			return;
		fs::remove_all(path);
	}

	void copyAll(const std::string& from, const std::string& to) const
	{
		fs::path sourceDir = from;
		fs::path targetDir = to;

		fs::create_directories(targetDir);

		for (const auto& entry : fs::directory_iterator(sourceDir))
		{
			const fs::path& path = entry.path();
			std::string relativePathStr = path.lexically_relative(sourceDir).string();
			fs::path targetPath = targetDir / relativePathStr;
			try
			{
				if (fs::is_directory(entry.status()))
				{
					fs::create_directories(targetPath);
					copyAll(path.string(), targetPath.string());
				}
				else if (fs::is_regular_file(entry.status()))
					fs::copy_file(path, targetPath, fs::copy_options::overwrite_existing);
				/*else
					std::cout << L"Пропущен файл \""_utf8 << path << "\"" << std::endl*/;
			}
			catch (fs::filesystem_error& e)
			{
				//std::cout << L"Ошибка переноса \""_utf8 << path << L"\" в \""_utf8 << targetPath << "\": " << e.what() << std::endl;
			}
		}
	}

	std::vector<std::string> getPathFrom(const std::string& path) const
	{
		std::vector<std::string> res;
		for (const auto& entry : fs::directory_iterator(path))
			if (entry.is_directory())
				res.push_back(entry.path().filename().string());
		return res;
	}

	void makePathIn(const std::string& path) const
	{
		fs::create_directory(path);
	}

	void makeFileWithText(const std::string& fName, const std::string& text)
	{
		std::ofstream out{ fName };
		out << text;
		out.close();
	}

private:

};