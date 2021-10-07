#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;

// Linked List
struct Ingredient
{
    char name[30];
    Ingredient *next;
};

// Circle Double Linked List 
struct Dessert 
{
    char name[30];
    Ingredient *ingredients;
    Dessert *prev, *next;
};

// Global Variables
Dessert *desserts;

// Function Prototype
void printDesserts();
bool hasDesserts();
Dessert* getDessert(int index);
void printIngredients(Dessert *dessert);
void addIngredient(Dessert *dessert, Ingredient *ingredient);
void removeIngredient(Dessert *dessert, char* name);
void addDessert(Dessert *dessert);
void addIngredients(Dessert *dessert);
void removeDessert(char* name);

/*
    [1] Print all the ingredients of a particle dessert
    [2] Insert an ingredient in a specific dessert
    [3] Remove an ingredient in a specific dessert
    [4] Insert a dessert (insert all its ingredients)
    [5] Remove a dessert (remove all its ingredients)
    [6] Quit program
*/

int main()
{
    // Init desserts list
    desserts = NULL;

    // Init option
    int op = 0;
    do 
    {
        system("cls");
        cout << "[1] Print all the ingredients of a particle dessert" << endl;
        cout << "[2] Insert an ingredient in a specific dessert" << endl;
        cout << "[3] Remove an ingredient in a specific dessert" << endl;
        cout << "[4] Insert a dessert (insert all its ingredients)" << endl;
        cout << "[5] Remove a dessert (remove all its ingredients)" << endl;
        cout << "[6] Quit program" << endl;

        fflush(stdin);
        cin >> op;

        switch(op)
        {
            case 1:
            {
                printDesserts();
                if (hasDesserts())
                {
                    int dessertIndex = 0;
                    cout << "Choose a dessert: ";
                    fflush(stdin);
                    cin >> dessertIndex;
                    Dessert *dessert = getDessert(--dessertIndex);
                    printIngredients(dessert);
                }
                break;
            }
            case 2:
            {
                printDesserts();
                if (hasDesserts())
                {
                    int dessertIndex = 0;
                    cout << "Choose a dessert: ";
                    fflush(stdin);
                    cin >> dessertIndex;
                    Dessert *dessert = getDessert(--dessertIndex);

                    cout << "Type the new ingredient: ";
                    char ingredientName[30];
                    fflush(stdin);
                    cin >> ingredientName;
                    Ingredient *newIngredient = new Ingredient;
                    strcpy(newIngredient->name, ingredientName);
                    addIngredient(dessert, newIngredient);
                }
                break;
            }
            case 3:
            {
                printDesserts();
                if (hasDesserts())
                {
                    int dessertIndex = 0;
                    cout << "Choose a dessert: ";
                    fflush(stdin);
                    cin >> dessertIndex;
                    Dessert *dessert = getDessert(--dessertIndex);

                    cout << "Type the ingredient to remove: ";
                    char ingredientName[30];
                    fflush(stdin);
                    cin >> ingredientName;
                    removeIngredient(dessert, ingredientName);
                }
                break;
            }
            case 4:
            {
                cout << "Type dessert name: ";
                char dessertName[30];
                fflush(stdin);
                cin >> dessertName;

                Dessert *newDessert = new Dessert;
                strcpy(newDessert->name, dessertName);
                newDessert->ingredients = NULL;
                addDessert(newDessert);
                addIngredients(newDessert);

                break;
            }
            case 5:
            {
                if (hasDesserts())
                {
                    cout << "Type dessert name: ";
                    char dessertName[30];
                    fflush(stdin);
                    cin >> dessertName;
                    removeDessert(dessertName);
                }
                else 
                {
                    cout << "There are no desserts to remove" << endl;
                }
                break;
            }
        }

        system("pause");
    }
    while (op != 6);
}

void printDesserts()
{
    cout << "Printing desserts: " << endl;
    Dessert *auxDessert = desserts;
    if (auxDessert == NULL)
    {
        cout << "There are no desserts to show" << endl;
        return;
    }

    Dessert *pivotDessert = desserts;
    int i = 1;
    do 
    {
        cout << "[" << i++ << "] " << auxDessert->name << endl;
        auxDessert = auxDessert->next;
    }
    while (auxDessert != pivotDessert);
}

bool hasDesserts()
{
    return desserts != NULL;
}

Dessert* getDessert(int index)
{
    Dessert *auxDessert = desserts;
    for (int i = 0; i < index; i++)
    {
        auxDessert = auxDessert->next;
    }

    return auxDessert;
}

void printIngredients(Dessert *dessert)
{
    cout << "Printing ingredients: " << endl;
    Ingredient *auxIngredient = dessert->ingredients;

    if (auxIngredient == NULL)
    {
        cout << "There are no ingredients to show" << endl;
        return;
    }

    int i = 1;
    while (auxIngredient != NULL)
    {
        cout << "[" << i++ << "] " << auxIngredient->name << endl;
        auxIngredient = auxIngredient->next;
    }
}

void addIngredient(Dessert *dessert, Ingredient *ingredient)
{
    if (dessert->ingredients == NULL)
    {
        dessert->ingredients = ingredient;
        dessert->ingredients->next = NULL;
        return;
    }

    Ingredient *auxIngredient = dessert->ingredients;
    while (auxIngredient->next != NULL)
    {
        auxIngredient = auxIngredient->next;
    } 

    auxIngredient->next = ingredient;
    auxIngredient = auxIngredient->next;
    auxIngredient->next = NULL;
}

void removeIngredient(Dessert *dessert, char* name)
{
    if (desserts->ingredients == NULL)
    {
        cout << "Ingredient \"" << name << "\" was not founded in ingredients" << endl;
        return;
    }

    Ingredient *auxIngredient = dessert->ingredients;
    while (auxIngredient != NULL && strcmp(auxIngredient->name, name) != 0)
    {
        auxIngredient = auxIngredient->next;
    }

    // Case 0: Unfounded
    if (auxIngredient == NULL)
    {
        cout << "Ingredient \"" << name << "\" was not founded in ingredients" << endl;
        return;
    }

    cout << "Ingredient \"" << name << "\" was founded in ingredients and was removed" << endl;

    // Case 1: Unique Node
    if (auxIngredient == dessert->ingredients && auxIngredient->next == NULL)
    {
        delete dessert->ingredients;
        dessert->ingredients = NULL;
        return;
    }

    // Case 2: First Node
    if (auxIngredient == dessert->ingredients)
    {
        auxIngredient = auxIngredient->next;
        delete dessert->ingredients;
        dessert->ingredients = auxIngredient;
        return;
    }

    // Case 3: Middle or Last Node
    Ingredient *aux02Ingredient = dessert->ingredients;
    while (aux02Ingredient->next != auxIngredient)
    {
        aux02Ingredient = aux02Ingredient->next;
    }

    aux02Ingredient->next = auxIngredient->next;
    delete auxIngredient;
}

void addDessert(Dessert *dessert)
{
    if (desserts == NULL)
    {
        desserts = dessert;
        dessert->next = dessert;
        dessert->prev = dessert;
    }

    Dessert *auxDessert = desserts->next;
    Dessert *pivotDessert = desserts;

    while(auxDessert != pivotDessert && strcmp(dessert->name, auxDessert->name) > 0)
    {
        auxDessert = auxDessert->next;
    }

    Dessert *aux02Dessert = auxDessert->prev;
    aux02Dessert->next = dessert;
    dessert->prev = aux02Dessert;
    dessert->next = auxDessert;
    auxDessert->prev = dessert;

    // Check if we need to move the header
    if (strcmp(dessert->name, pivotDessert->name) < 0)
    {
        desserts = dessert;
    }
}

void addIngredients(Dessert *dessert)
{
    int op = 1;

    do 
    {
        cout << "[1] Add another ingredient" << endl;
        cout << "[0] Back to menu" << endl;
        fflush(stdin);
        cin >> op;
        if (op == 1)
        {
            cout << "Type the new ingredient: ";
            char ingredientName[30];
            fflush(stdin);
            cin >> ingredientName;
            Ingredient *newIngredient = new Ingredient;
            strcpy(newIngredient->name, ingredientName);
            addIngredient(dessert, newIngredient);
        }
    }
    while (op != 0);
}

void removeDessert(char* name)
{
    if (desserts == NULL)
    {
        return;
    }

    Dessert *auxDessert = desserts->next;
    Dessert *pivotDessert = desserts;

    while(auxDessert != pivotDessert && strcmp(name, auxDessert->name) != 0)
    {
        auxDessert = auxDessert->next;
    }

    // Case 0: Unfounded dessert
    if (auxDessert == pivotDessert && strcmp(name, auxDessert->name) != 0)
    {
        cout << "Dessert \"" << name << "\" was not founded" << endl;
        return;
    }

    // Remove Ingredients
    Ingredient *ingredient = auxDessert->ingredients;
    while (ingredient != NULL)
    {
        removeIngredient(auxDessert, ingredient->name);
        ingredient = ingredient->next;
    }

    // Case Unique Node
    if (desserts->next == desserts)
    {
        delete auxDessert;
        desserts = NULL;
        return;
    }

    Dessert *aux02Dessert = auxDessert->prev;
    aux02Dessert->next = auxDessert->next;
    auxDessert->next->prev = aux02Dessert;

    // Move header if it's requiered
    if (desserts == auxDessert)
    {
        desserts = auxDessert->next;
    }

    delete auxDessert;
}