#pragma once


namespace Paths {
	enum class CutterType;
}

class QString;

class PathsGenerator
{
public:
	PathsGenerator();

	void savePaths(float radius, Paths::CutterType type, const QString &path) const;
	void generateCrudePaths(const QString& fileContent);
private:
};
