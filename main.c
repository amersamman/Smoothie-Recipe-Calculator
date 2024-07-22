#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structs
typedef struct item {
int itemNo;
int portions;
} item;

typedef struct recipe {
int itemCount;
item* itemList;
int totalPortions;
} recipe;


//Gets amount of ingredients, allocates memory, fills data.
char** readIngredients(int *numIngredients)
{
  scanf("%d", numIngredients);
  char** ingredients = malloc(*numIngredients * sizeof(char*));

  for(int i=0; i< *numIngredients; i++){
    char ingredient[21];
    scanf("%s", ingredient);
    int length = strlen(ingredient) + 1;
    ingredients[i] = (char*)malloc(length * sizeof(char));
    strcpy(ingredients[i], ingredient);
  }
  return ingredients;
}

//Allocates memory for smoothie, gets itemNo, and portions.
recipe* readRecipe(){
  recipe* smoothie = malloc(sizeof(recipe));
  scanf("%d", &(smoothie->itemCount));
  smoothie->itemList = (item*)malloc(smoothie->itemCount * sizeof(item));
  smoothie->totalPortions = 0;
  for(int i=0; i< smoothie->itemCount; i++)
    {
      scanf("%d %d", &smoothie->itemList[i].itemNo, &smoothie->itemList[i].portions);
      smoothie->totalPortions += smoothie->itemList[i].portions;
    }
  return smoothie;
}

//Gets the number of recipes, allocates memory, fills data from readRecipe.
recipe** readAllRecipes(int *numRecipes){
  scanf("%d", numRecipes);
  recipe** allRecipes = malloc(*numRecipes * sizeof(recipe*));
  for(int i=0; i< *numRecipes; i++)
    {
      allRecipes[i] = readRecipe();
    }
  return allRecipes;
}

//Caculates order of ingredients.
double* calculateOrder(int ingredientCount, int numSmoothies, recipe** recipeList){
  double* order = calloc(ingredientCount, sizeof(double));
  for(int i=0; i< numSmoothies; i++)
    {
      int smoothieNo, weight;

      scanf("%d %d", &smoothieNo, &weight);
      recipe* currentRecipe = recipeList[smoothieNo];

      for(int j=0; j< currentRecipe->itemCount; j++)
      {
        int itemNo = currentRecipe->itemList[j].itemNo;
        int portions = currentRecipe->itemList[j].portions;
        order[itemNo] += (double)portions * weight / currentRecipe->totalPortions;
      }
    }
  return order;
}

//Prints order of ingredients.
void printOrder(char** ingredientNames, double* orderList, int numIngredients){
  for(int i=0; i< numIngredients; i++)
  {
    if(orderList[i] > 0)
    {
      printf("%s %.6lf\n", ingredientNames[i], orderList[i]);
    }
  }
  printf("\n");
}

//Frees memory allocated for ingredients.
void freeIngredients(char** ingredientList, int numIngredients){
  for(int i=0; i< numIngredients; i++){
    free(ingredientList[i]);
  }
  free(ingredientList);
}

//Frees memory allocated for recipes.
void freeRecipes(recipe** allRecipes, int numRecipes){
  for(int i=0; i< numRecipes; i++)
    {
      free(allRecipes[i]->itemList);
      free(allRecipes[i]);
    }
  free(allRecipes);
}

//Main
int main(){

  int numIngredients, numRecipes, numStores;

  char** ingredients = readIngredients(&numIngredients);
  recipe** recipes = readAllRecipes(&numRecipes);

  scanf("%d", &numStores);
  for(int i = 0; i < numStores; i++)
  {
    int numSmoothies;
    scanf("%d", &numSmoothies); 
    double* order = calculateOrder(numIngredients, numSmoothies, recipes);
    printf("List of items for store %d:\n", i+1);
    printOrder(ingredients, order, numIngredients);
    free(order);
  }

  freeIngredients(ingredients, numIngredients);
  freeRecipes(recipes, numRecipes);

  return 0;
  
}

