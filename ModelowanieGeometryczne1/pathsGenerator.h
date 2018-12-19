#pragma once
#include <vector>


namespace Paths {
	enum class CutterType;
}

class QString;
class QVector3D;

class PathsGenerator
{
public:
	PathsGenerator();

	void savePaths(float radius, Paths::CutterType type, const QString &path) const;
	void generateCrudePaths(const QString& fileContent) const;
	void generateCleaningPaths(const QString& fileContent) const;

private:
	std::vector<QVector3D> trimPaths(const std::vector<QVector3D> &paths) const;
	bool compareFloats(float a, float b) const;
};
