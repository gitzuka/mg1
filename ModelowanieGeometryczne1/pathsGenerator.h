#pragma once
#include <vector>


namespace Paths {
	enum class CutterType;
}

class QString;
class QVector3D;
class QVector4D;

class PathsGenerator
{
public:
	PathsGenerator();

	void savePaths(float radius, Paths::CutterType type, const QString &path) const;
	void generateCrudePaths(const QString& fileHeightmap) const;
	void generateCleaningPaths(const QString& fileHeightmap) const;
	void generateEnvelopePaths(const std::vector<QVector4D> &outer, const std::vector<QVector4D>& inner) const;

private:
	std::vector<QVector3D> trimPaths(const std::vector<QVector3D> &paths) const;
	bool compareFloats(float a, float b) const;
};
