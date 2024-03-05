#include "NPC.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "glm/geometric.hpp"

NPC::NPC()
{
}

NPC::NPC(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

NPC::~NPC()
{
}

void NPC::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{
	Character::AttachGeometry(_renderBoxReference, _hitBoxReference);
}

void NPC::BeginPlayCharacter()
{
	Character::BeginPlayCharacter();


	if(CurrentPathType == Aproximate)
		Path = ReadAproximatePath("AproximatePath.txt");
	else 
		Path = ReadInterpolatedPath("InterpolatedPath.txt");
	
}

void NPC::TickCharacter(float deltatime)
{
	Character::TickCharacter(deltatime);

	
	if(Path.size() > 0)
		MoveAlongPath(deltatime);
}

void NPC::ChangePath()
{

	if (CurrentPathType == Aproximate)
		Path = ReadInterpolatedPath("InterpolatedPath.txt");
	
	else
		Path = ReadAproximatePath("AproximatePath.txt");

}

std::vector<vec3> NPC::ReadAproximatePath(const char* _filePath)
{

	std::ifstream GeometryFile;
	// Open the txt file containing geometry data.
	GeometryFile.open(_filePath);

	// First line defines how many lines there are total
	// Extract and convert to int
	std::string numLinesStr;
	std::getline(GeometryFile, numLinesStr);
	int numLinesInt = stoi(numLinesStr);

	std::string numVariablesStr;
	getline(GeometryFile, numVariablesStr);
	int numVariablesInt = stoi(numVariablesStr);

	// Create a vector to contain all vertexes generated. 
	std::vector<vec3> temp;

	// Iterates through the total number of lines. 
	for (int i = 0; i < numLinesInt; i++)
	{
		// Gets the first line as a string, removes all spaces and parentheses
		std::string tempLines, result1, result2, result3;
		getline(GeometryFile, tempLines);
		std::remove_copy(tempLines.begin(), tempLines.end(), std::back_inserter(result1), ' ');
		std::remove_copy(result1.begin(), result1.end(), std::back_inserter(result2), '(');
		std::remove_copy(result2.begin(), result2.end(), std::back_inserter(result3), ')');

		// Pre defines variables for converting from string to float.
		float x = 0, y = 0, z = 0;

		// Iterates through number of variables in current line
		for (int i = 0; i < numVariablesInt; i++)
		{
			// Gets the index between start and first number end defined by ','.
			int lastPosNumIndex = result3.find(',');
			// Copies this value into sting
			std::string final(result3.begin(), result3.begin() + lastPosNumIndex);
			// Erases that value from complete string
			result3.erase(result3.begin(), result3.begin() + lastPosNumIndex + 1);

			// Switch case to convert value to proper variable
			switch (i + 1)
			{
			case 1:
				x = stof(final);
				break;
			case 2:
				y = stof(final);
				break;
			case 3:
				z = stof(final);
				break;
			default:
				// Error handling if default case triggered. 
				std::cout << "ERROR::READING_GEOMETRY_FILE::NO_MORE_VERTEX_ATTRIBUTE_LINES";
				break;
			}
		}

		// creates the new vertex with the given variables.
		temp.push_back(vec3(x-1,z+4,y+3));
	}

	// close file when finished reading it
	GeometryFile.close();

	if(temp.size()> 0)
	{
		MovementVector = WorldPosition - temp[0];
		GoalPoint = temp[0];
	}

	return temp;
}

std::vector<vec3> NPC::ReadInterpolatedPath(const char* _filePath)
{
	std::ifstream GeometryFile;
	// Open the txt file containing geometry data.
	GeometryFile.open(_filePath);

	// First line defines how many lines there are total
	// Extract and convert to int
	std::string numLinesStr;
	std::getline(GeometryFile, numLinesStr);
	int numLinesInt = stoi(numLinesStr);

	std::string numVariablesStr;
	getline(GeometryFile, numVariablesStr);
	int numVariablesInt = stoi(numVariablesStr);

	// Create a vector to contain all vertexes generated. 
	std::vector<vec3> temp;

	// Iterates through the total number of lines. 
	for (int i = 0; i < numLinesInt; i++)
	{
		// Gets the first line as a string, removes all spaces and parentheses
		std::string tempLines, result1, result2, result3;
		getline(GeometryFile, tempLines);
		std::remove_copy(tempLines.begin(), tempLines.end(), std::back_inserter(result1), ' ');
		std::remove_copy(result1.begin(), result1.end(), std::back_inserter(result2), '(');
		std::remove_copy(result2.begin(), result2.end(), std::back_inserter(result3), ')');

		// Pre defines variables for converting from string to float.
		float x = 0, y = 0, z = 0;

		// Iterates through number of variables in current line
		for (int i = 0; i < numVariablesInt; i++)
		{
			// Gets the index between start and first number end defined by ','.
			int lastPosNumIndex = result3.find(',');
			// Copies this value into sting
			std::string final(result3.begin(), result3.begin() + lastPosNumIndex);
			// Erases that value from complete string
			result3.erase(result3.begin(), result3.begin() + lastPosNumIndex + 1);

			// Switch case to convert value to proper variable
			switch (i + 1)
			{
			case 1:
				x = stof(final);
				break;
			case 2:
				y = stof(final);
				break;
			case 3:
				z = stof(final);
				break;
			default:
				// Error handling if default case triggered. 
				std::cout << "ERROR::READING_GEOMETRY_FILE::NO_MORE_VERTEX_ATTRIBUTE_LINES";
				break;
			}
		}

		// creates the new vertex with the given variables.
		temp.push_back(vec3(x - 3, z + 4, y + 7));
	}

	// close file when finished reading it
	GeometryFile.close();

	if (temp.size() > 0)
	{
		MovementVector = WorldPosition - temp[0];
		GoalPoint = temp[0];
	}

	return temp;
}

void NPC::MoveAlongPath(float deltatime)
{
	if(MoveToPoint(deltatime))
	{
		PathIt += 1;

		if(PathIt<Path.size())
		{
			GoalPoint = Path[PathIt];
			MovementVector = WorldPosition - GoalPoint;
		}

		if (PathIt == Path.size()-1)
		{
			std::reverse(Path.begin(), Path.end());
			PathIt = 0;
			GoalPoint = Path[PathIt+1];
			MovementVector = WorldPosition - GoalPoint;
		}
	}
}

bool NPC::MoveToPoint(float deltatime)
{
	WorldPosition -= MovementVector * deltatime * MovementSpeed;
	// Calculate the distance between WorldPosition and GoalPoint
	float distance = glm::distance(WorldPosition, GoalPoint);

	// Assuming you want to check if the distance is less than or equal to some threshold (epsilon)
	float limit = 0.01f; // Adjust the epsilon value based on your requirements

	if (distance <= limit)
	{
		return true;
	}
	return false;
}
