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

class StockManager {
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;

public:
    StockManager() {};
    // 재고 초기화
    void initializeStock(std::string potionName) {
        potionStock.insert({ potionName, MAX_STOCK });
    }

    // 물약 지급
    bool dispensePotion(std::string potionName) {
        if (potionStock[potionName] <= 0) {
            return false;
        }
        else {
            potionStock[potionName]--;
            return true;
        }
    }

    // 공병 반환 및 포션 보충
    void returnPotion(std::string potionName) {
        if (potionStock.find(potionName) == potionStock.end()) std::cout << "해당 이름의 물약이 존재하지 않습니다." << std::endl;
        else{
            if (potionStock[potionName] >= MAX_STOCK) {
                std::cout << "재고가 가득 차있습니다." << std::endl;
            }
            else{
                std::cout << "빈병을 돌려받아 " << potionName << "의 재고를 채웠습니다." << std::endl;
                potionStock[potionName]++;
            }
        }
    }
    // 현재 포션  재고 반환
    int getStock(std::string potionName) {
        return potionStock[potionName];
    }
};

class AlchemyWorkshop{
    private:
        StockManager stockManager;
        std::vector<PotionRecipe> recipes;

    public:
        bool requestPotion(std::string& name) {
            return stockManager.dispensePotion(name);
        }

        void returnPotion(std::string& name) {
            stockManager.returnPotion(name);
        }
        
        int getStockWithName(std::string& name) {
            return stockManager.getStock(name);
        }

        void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
            recipes.push_back(PotionRecipe(name, ingredients));
            std::cout << ">> 새로운 레시피 '"<<name <<"'이(가) 추가되었습니다." << std::endl;
            // 추가된 레시피의 물약의 재고를 3으로 초기화시켜주기
            stockManager.initializeStock(name);
        }

        void displayAllRecipes() {
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
                std::cout << " > 재고 : " << stockManager.getStock(recipes[i].potionName) << std::endl;
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

        // const + & 써서 참조자로 값을 가져오면 복사없이 출력가능하기때문에 성능이 더 좋아짐
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


int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 레시피 이름으로 검색" << std::endl;
        std::cout << "4. 재료 이름으로 검색" << std::endl;
        std::cout << "5. 공병 반환" << std::endl;
        std::cout << "6. 종료" << std::endl;
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

            std::cout << myWorkshop.serchRecipeByName(name).potionName << "의 재고는 " << myWorkshop.getStockWithName(name) << "개 입니다. 받으시겠습니까?" << std::endl;

            std::cout << "1. 예\n" << "2. 아니오" << std::endl;
            std::cin >> choice;
            if (choice == 1) {
                if (myWorkshop.requestPotion(name)) std::cout << "물약을 수령했습니다." << std::endl;
                else std::cout << "물약의 재고가 부족합니다." << std::endl;
            }
            else if (choice == 2) {
                std::cout << "수령을 거절했습니다." << std::endl;
                continue;
            }
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
                std::cout << ingredient << " 가 들어가는 물약\n";
                for (int i = 0; i < myWorkshop.serchRecipeByIngredient(ingredient).size(); ++i) {
                    std::cout << i+1 << ". " << myWorkshop.serchRecipeByIngredient(ingredient)[i].potionName << " , 재고 : " << myWorkshop.getStockWithName(myWorkshop.serchRecipeByIngredient(ingredient)[i].potionName) << std::endl;
                }

                std::cout << "받을 물약을 선택하십시오" << std::endl << "받지않으실꺼면 0을 입력하십시오." << std::endl;
                std::cin >> choice;
                while (true) {
                    if (choice == 0) {
                        std::cout << "수령을 거절했습니다." << std::endl;
                        break;
                    }

                    if (choice > myWorkshop.serchRecipeByIngredient(ingredient).size()) {
                        std::cout <<"잘못된 입력입니다. 다시 입력하십시오" << std::endl;
                    }
                    else {
                        if (myWorkshop.requestPotion(myWorkshop.serchRecipeByIngredient(ingredient)[choice - 1].potionName)) {
                            std::cout << "물약을 수령했습니다." << std::endl;
                            break;
                        }
                        else {
                            std::cout << "물약의 재고가 부족합니다." << std::endl;
                            break;
                        }
                    }
                }
            }
        }
        else if (choice == 5) {
            std::string name;
            std::cout <<"반환할 물약의 이름을 입력하십시오 : " ;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            myWorkshop.returnPotion(name);
        }
        else if (choice == 6) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}