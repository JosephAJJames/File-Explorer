#include <iostream>
#include <filesystem>
#include <regex>
#include <stack>

namespace fs = std::filesystem;

class FileExplorer
{
private:
    fs::path currentPath;
    std::stack<fs::path> myStack;

public:
    FileExplorer()
    {
        currentPath = fs::current_path().root_path();
    }

    bool validPath(const std::string &path)
    {
        const std::regex pattern(R"(^[a-zA-Z]:\\(?:[^<>:""/\\|?*]+\\)*[^<>:""/\\|?*]*$)");

        return std::regex_match(path, pattern);
    }

    void cwd()
    {
        std::cout << currentPath << std::endl;
    }

    void cd(const std::string &path)
    {
        if (validPath(path))
        {
            currentPath = fs::absolute(path);
        }
        else
        {
        }
    }

    void ls()
    {
        for (const auto &entry : fs::directory_iterator(currentPath))
        {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    void run()
    {
        bool run = true;
        while (run)
        {
            std::cout << "What would you like to do?:\n";
            std::cout << "1. Change directory\n";
            std::cout << "2. Print working directory\n";
            std::cout << "3. List contents\n";
            int num = 0;
            std::cout << "Enter an integer: ";
            std::cin >> num;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (num == 1)
            {
                std::string inputStr;
                bool flag;
                do
                {
                    inputStr;
                    std::cout << "Please enter the path to change to\n";
                    std::cout << "Enter a string: ";
                    std::getline(std::cin, inputStr);
                    if (inputStr == ".." || inputStr == "-")
                    {
                        flag = true;
                        break;
                    }
                } while (validPath(inputStr));
                if (flag)
                {
                    if (inputStr == "..")
                    {
                        inputStr = currentPath.parent_path().string();
                    }
                    else
                    {
                        inputStr = myStack.top().string();
                        myStack.pop();
                    }
                }
                myStack.push(currentPath);
                currentPath = fs::path(inputStr);
            }
            else if (num == 2)
            {
                std::cout << "\n";
                cwd();
            }
            else if (num == 3)
            {
                std::cout << "\n";
                ls();
            }
            else
            {
                std::cout << "Please enter a valid number option\n";
            }
        }
    }
};

int main()
{
    FileExplorer explorer;
    explorer.run();
}