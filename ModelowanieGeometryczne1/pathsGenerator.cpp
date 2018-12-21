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
	//float radius = 0.8f;
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

void PathsGenerator::generateCleaningPaths(const QString &fileHeightmap) const
{
	int width, height;
	float *heightmap = fileManager::loadHeightmap(fileHeightmap, height, width);
	int yStep = 1;
	int xStep = 75;
	float heightMilling = 20.0f;
	float heightHM = 2.0f;
	float safeHeight = 80;
	float bound = 75;
	std::vector<QVector3D> paths;
	paths.reserve(width * height / 100);
	paths.emplace_back(QVector3D(0, 0, safeHeight));
	paths.emplace_back(QVector3D(-bound, -bound, safeHeight));
	paths.emplace_back(QVector3D(-bound, -bound, heightMilling));
	paths.emplace_back(QVector3D(xStep / 10.0f - 75, - 75, heightMilling));
	for (int i = xStep; i < width; i += xStep)
	{
		std::vector<QVector3D> partialPath;
		partialPath.reserve(height / 10);
		for (int j = 0; j <= height; j += yStep)
		{

			partialPath.emplace_back(QVector3D(i / 10.0f - bound, j / 10.0f - bound, heightMilling));
			if (heightmap[i * width + j] >= heightHM)
			{
				break;
			}
		}
		partialPath = trimPaths(partialPath);
		i % 2 == 0 ?
			paths.insert(paths.end(), std::make_move_iterator(partialPath.rbegin()), std::make_move_iterator(partialPath.rend()))
			: paths.insert(paths.end(), std::make_move_iterator(partialPath.begin()), std::make_move_iterator(partialPath.end()));

	}
	paths.emplace_back(QVector3D(paths[paths.size() - 2].x(), paths[paths.size() - 2].y(), heightMilling));
	//paths.emplace_back(QVector3D((width - xStep / 2) / 10.0f - bound, 0 / 10.0f - bound, heightMilling));
	paths.emplace_back(QVector3D(width  / 10.0f - bound, 0 / 10.0f - bound, heightMilling));
	paths.emplace_back(QVector3D(width  / 10.0f - bound, height / 10.0f - bound, heightMilling));
	//paths.emplace_back(QVector3D(width  / 10.0f - bound, height / 10.0f - bound, heightMilling));
	/*int y = -1;
	for (int j = 0; j <= height; j += yStep)
	{
		if (heightmap[(width - xStep / 2) * width + j] >= heightHM)
		{
			y = j / 10.0f - 75;
			paths.emplace_back(QVector3D(width / 10.0f - 75, j / 10.0f - 75, heightMilling));
			break;
		}
	}
	paths.emplace_back(QVector3D(width / 10.0f - 75 + 6, y, heightMilling));
*/


	for (int i = width - xStep; i > 0; i -= xStep)
	{
		std::vector<QVector3D> partialPath;
		partialPath.reserve(height / 10);
		for (int j = height; j > 0; j -= yStep)
		{
			partialPath.emplace_back(QVector3D(i / 10.0f - bound, j / 10.0f - bound, heightMilling));
			if (heightmap[i * width + j] >= heightHM)
			{
			//qDebug("collision " + QString::number(j).toLatin1());
				break;
			}
		}
		partialPath = trimPaths(partialPath);
		i % 2 == 0 ?
			paths.insert(paths.end(), std::make_move_iterator(partialPath.rbegin()), std::make_move_iterator(partialPath.rend()))
			: paths.insert(paths.end(), std::make_move_iterator(partialPath.begin()), std::make_move_iterator(partialPath.end()));

	}

	paths.emplace_back(QVector3D(paths[paths.size() - 2].x(), paths[paths.size() - 2].y(), heightMilling));
	paths.emplace_back(QVector3D(-bound, height / 10.0f - bound, heightMilling));
	paths.emplace_back(QVector3D(-bound, - bound, heightMilling));


	paths.emplace_back(QVector3D(paths[paths.size() - 1].x(), paths[paths.size() - 1].y(), safeHeight));
	paths.emplace_back(QVector3D(0, 0, safeHeight));

	QString path = "a2.f12";
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

void PathsGenerator::generateEnvelopePaths(const std::vector<QVector4D>& positions) const
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
	}
	trimmed.emplace_back(paths[paths.size() - 1]);
	return trimmed;
}

bool PathsGenerator::compareFloats(float a, float b) const
{
	float eps = 0.001f;
	return abs(a - b) < eps;
}
