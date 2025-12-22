#include <iostream>
#include <vector>
#include <string>
#include <map>

class PotionRecipe {
    public:
        std::string potionName;
        std::vector<std::string> ingredients;

        PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
            : potionName(name), ingredients(ingredients){}
};

class AlchemyWorkshop {
    private:
        std::vector<PotionRecipe> recipes;

    public:
        void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
            recipes.push_back(PotionRecipe(name, ingredients));
            std::cout << ">> 새로운 레시피 '"<<name <<"'이(가) 추가되었습니다." << std::endl;
        }

        void displayAllRecipes() const {
            if (recipes.empty()) {
                std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
                return;
            }

            std::cout << "\n--- [ 전체 레시피 목록 ] ---" <<std::endl;
            for (size_t i = 0; i < recipes.size(); ++i) {
                std::cout << "- 물약 이름 : " << recipes[i].potionName << std::endl;
                std::cout << " > 필요 재료 : ";

                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                    std::cout << recipes[i].ingredients[j];
                    if (j < recipes[i].ingredients.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << "--------------------------------------\n";
        }

        PotionRecipe serchRecipeByName(std::string potionName) {
            for (int i = 0; i < recipes.size(); ++i) {
                if (recipes[i].potionName == potionName) {
                    return recipes[i];
                }
            }
            return PotionRecipe("",{ });
        }

        std::vector<PotionRecipe> serchRecipeByIngredient(std::string ingredient) {
            std::vector<PotionRecipe> serchResult;
            for (int i = 0; i < recipes.size(); ++i) {
                for (int j = 0; j < recipes[i].ingredients.size(); ++j) {
                    if (recipes[i].ingredients[j] == ingredient) {
                        serchResult.push_back(recipes[i]);
                        break;
                    }
                }
            }
            return serchResult;
        }
};

class StockManager{
    private:
        std::map<std::string,int> potionStock;
        const int MAX_STOCK = 3;

    public:
        void initializeStock(std::string potionName) {

        }

        bool dispensePotion(std::string potionName) {

        }

        void returnPotion(std::string potionName) {

        }

        int getStock(std::string potionName) {

        }
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 레시피 이름으로 검색" << std::endl;
        std::cout << "4. 재료 이름으로 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string name;
            std::cout << "검색할 물약이름 : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
        
            if (myWorkshop.serchRecipeByName(name).potionName == "") {
                std::cout << "해당 이름의 물약 제조법은 없습니다." << std::endl;
            }

            std::cout << myWorkshop.serchRecipeByName(name).potionName << "의 재료는\n";
            for(int i = 0 ; i < myWorkshop.serchRecipeByName(name).ingredients.size(); ++i){
                std::cout << myWorkshop.serchRecipeByName(name).ingredients[i] << ' ';
            }
            std::cout << " 입니다." << std::endl;
        }
        else if (choice == 4) {
            std::string ingredient;
            std::cout << "검색할 재료 이름 : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ingredient);
            
            if (myWorkshop.serchRecipeByIngredient(ingredient).size() == 0) {
                std::cout << "해당 재료가 들어가는 레시피가 없습니다." << std::endl;
            }
            else{
                std::cout << ingredient << " 가 들어가는 물약은\n";
                for (int i = 0; i < myWorkshop.serchRecipeByIngredient(ingredient).size(); ++i) {
                    std::cout << myWorkshop.serchRecipeByIngredient(ingredient)[i].potionName << ' ';
                }
                std::cout << " 입니다." << std::endl;
            }
        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}