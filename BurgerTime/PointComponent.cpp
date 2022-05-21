#include "PointComponent.h"
#include <fstream>
#include <iostream>
#include <cassert>

PointComponent::PointComponent(const std::shared_ptr<dae::GameObject>& gameObject, int startingPoints)
	:Component(gameObject)
	, m_StartingPoints(startingPoints)
	, m_CurrentPoints(startingPoints)
{}

void PointComponent::SavePointsToFile(const std::string&)
{
    //Reading the file -------------------------------------------------------
    std::ifstream input;
    //input.open(fileName);

    //if (!input)
    //{
    //    std::cout << "Cannot open file (read)" << std::endl;
    //    exit;
    //}

    //if (input.is_open())
    //{
    //    std::string line;
    //    while (std::getline(input, line))
    //    {
    //        std::reverse(line.begin(), line.end());
    //        //input >> line;
    //        text.emplace_back(line); //save line to vector
    //    }

    //    std::reverse(text.begin(), text.end());

    //    std::string reverseTitle = title;
    //    std::reverse(reverseTitle.begin(), reverseTitle.end());

    //    //Writing to the file ----------------------------------------------------
    //    std::ofstream newFile;
    //    newFile.open(reverseTitle, std::ios::binary);  //Creates file with name and type
    //    if (!newFile)
    //    {
    //        std::cout << "Cannot open file (write)" << std::endl;
    //        exit;
    //    }

    //    for (std::string str : text)
    //    {
    //        newFile << str << std::endl;
    //    }
    //}
    //else
    //{
    //    std::cout << "File not found" << std::endl;
    //}
}

std::shared_ptr<dae::Component> PointComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PointComponent>(gameObject, m_StartingPoints);
}
