#include "pathsGenerator.h"
#include "fileManager.h"
#include "pathsUtils.h"

PathsGenerator::PathsGenerator()
{
}

void PathsGenerator::savePaths(float radius, Paths::CutterType type, const QString &path) const
{

}

void PathsGenerator::generateCrudePaths(const QString &fileHeightmap)
{
	int width, height;
	float *heightmap = fileManager::loadHeightmap(fileHeightmap, height, width);
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (heightmap[i * width + j] > 2.0f)
			{
				
			}
		}
	}
}
