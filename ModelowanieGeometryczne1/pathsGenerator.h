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
	void generateEnvelopePaths(const std::vector<QVector4D> &outer) const;
	/*void generatePrecisePathsSmiglo(std::vector<std::vector<QVector4D>> &positions) const;
	void generatePrecisePathsPodstawka(std::vector<std::vector<QVector4D>> &positions) const;
	void generatePrecisePathsKadlub(std::vector<std::vector<QVector4D>> &positions) const;
	void generatePrecisePathsPloza(std::vector<std::vector<QVector4D>> &positions) const;*/
	void clearFile(const QString& file) const;

private:
	std::vector<QVector3D> trimPaths(const std::vector<QVector3D> &paths) const;
	std::vector<std::vector<QVector3D>> convertPrecisePaths(const std::vector<std::vector<QVector4D>> &positions) const;
	bool compareFloats(float a, float b) const;
	QVector3D getPosition(const QString &position) const;
};
