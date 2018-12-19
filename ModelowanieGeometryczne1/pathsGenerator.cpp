#include "pathsGenerator.h"
#include "fileManager.h"
#include "pathsUtils.h"

PathsGenerator::PathsGenerator()
{
}

void PathsGenerator::savePaths(float radius, Paths::CutterType type, const QString &path) const
{

}

void PathsGenerator::generateCrudePaths(const QString &fileHeightmap) const
{
	int width, height;
	float *heightmap = fileManager::loadHeightmap(fileHeightmap, height, width);
	float radius = 0.8f;
	std::vector<QVector3D> paths;
	paths.reserve(width * height / 100);
	paths.emplace_back(QVector3D(0, 0, 80));
	paths.emplace_back(QVector3D(-75, -75, 80));
	float conversionFactor = 10;
	float initialHeight = 3.5f;
	float secondHeight = 2.1f;
	int yStep = 30;
	int xStep = 115;
	for (int i = 0; i < width; i += xStep)
	{
		std::vector<QVector3D> partialPath;
		partialPath.reserve(height / 10);
		for (int j = 0; j <= height; j += yStep)
		{

			if (heightmap[i * width + j] >= initialHeight)
				partialPath.emplace_back(QVector3D(i / 10.0f - 75, j / 10.0f - 75, heightmap[i * width + j] * conversionFactor));
			else
				partialPath.emplace_back(QVector3D(i / 10.0f - 75, j / 10.0f - 75, initialHeight * conversionFactor));
		}
		partialPath = trimPaths(partialPath);
		i % 2 == 1 ?
			paths.insert(paths.end(), std::make_move_iterator(partialPath.rbegin()), std::make_move_iterator(partialPath.rend()))
			: paths.insert(paths.end(), std::make_move_iterator(partialPath.begin()), std::make_move_iterator(partialPath.end()));

	}

	paths.emplace_back(QVector3D(paths[paths.size() - 1].x(), paths[paths.size() - 1].y(), 80));
	paths.emplace_back(QVector3D(-75, -75, 80));

	for (int i = 0; i < width; i += xStep)
	{
		std::vector<QVector3D> partialPath;
		partialPath.reserve(height / 10);
		for (int j = 0; j <= height; j += yStep)
		{

			if (heightmap[i * width + j] >= secondHeight)
				partialPath.emplace_back(QVector3D(i / 10.0f - 75, j / 10.0f - 75, heightmap[i * width + j] * conversionFactor));
			else
				partialPath.emplace_back(QVector3D(i / 10.0f - 75, j / 10.0f - 75, secondHeight * conversionFactor));
		}
		partialPath = trimPaths(partialPath);
		i % 2 == 1 ?
			paths.insert(paths.end(), std::make_move_iterator(partialPath.rbegin()), std::make_move_iterator(partialPath.rend()))
			: paths.insert(paths.end(), std::make_move_iterator(partialPath.begin()), std::make_move_iterator(partialPath.end()));

	}
	paths.emplace_back(QVector3D(paths[paths.size() - 1].x(), paths[paths.size() - 1].y(), 80));
	paths.emplace_back(QVector3D(0, 0, 80));

	QString path = "a1.k16";
	QFile outputFile(path);
	outputFile.open(QFile::ReadWrite | QIODevice::Truncate | QIODevice::Text);

	QTextStream out(&outputFile);

	for (int i = 0; i < paths.size(); i++)
	{
		out << "N" << QString::number(i) << "G01" << "X" << QString::number(paths.at(i).x(), 'f', 3).toUtf8() << "Y" << QString::
			number(paths.at(i).y(), 'f', 3).toUtf8() << "Z" << QString::number(paths.at(i).z(), 'f', 3).toUtf8() << endl;
	}
	outputFile.close();
}

void PathsGenerator::generateCleaningPaths(const QString& fileContent) const
{

}

std::vector<QVector3D> PathsGenerator::trimPaths(const std::vector<QVector3D> &paths) const
{
	std::vector<QVector3D> trimmed;
	trimmed.reserve(paths.size());
	bool prev = false;

	for (int i = 0; i < paths.size() - 1; ++i)
	{
		bool a = compareFloats(paths[i].z(), paths[i + 1].z());
		bool b = compareFloats(paths[i].x(), paths[i + 1].x());
		bool c = compareFloats(paths[i].y(), paths[i + 1].y());
		if (a && b || a && c)
		{
			if (!prev)
			{
				trimmed.emplace_back(paths[i]);
				prev = true;
			}
			continue;

		}
		trimmed.emplace_back(paths[i]);
		prev = false;
		//if (!compareFloats(paths[i].z(), paths[i + 1].z()) && !(compareFloats(paths[i].x(), paths[i + 1].x()) || compareFloats(paths[i].y(), paths[i + 1].y())))
		//	trimmed.emplace_back(paths[i]);
		//else if (compareFloats(paths[i].x(), paths[i].x()) || compareFloats(paths[i].y(), paths[i].y()))

	}
	trimmed.emplace_back(paths[paths.size() - 1]);
	return trimmed;
}

bool PathsGenerator::compareFloats(float a, float b) const
{
	float eps = 0.001f;
	return abs(a - b) < eps;
}
