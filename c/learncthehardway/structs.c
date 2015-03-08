#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *name;
    int age;
    int height;
} Person;

typedef struct {
    short age;
    long height;
} Dummy;

Person *create_person(char *name, int age, int height);
void delete_person(Person *person);
void print_person(Person *person);
void years_later(Person *person, int years);


int main()
{
    printf("size of short is %ld\n", sizeof(short));
    printf("size of int is %ld\n", sizeof(int));
    printf("size of long is %ld\n", sizeof(long));
    printf("size of long long is %ld\n", sizeof(long long));
    printf("size of Person is %ld\n", sizeof(Person));
    printf("size of Dummy is %ld\n", sizeof(Dummy));
    printf("\n");

    Person *tommy = create_person("Tommy", 2, 20);
    Person *tina = create_person("Tina", 17, 155);

    printf("%s live at %p\n", tommy->name, tommy);
    print_person(tommy);

    printf("\n");
    printf("%s live at %p\n", tina->name, tina);
    print_person(tina);

    printf("\n");
    years_later(tommy, 3);
    years_later(tina, 3);
    printf("3 years later ...\n");

    printf("\n");
    printf("%s live at %p\n", tommy->name, tommy);
    print_person(tommy);

    printf("\n");
    printf("%s live at %p\n", tina->name, tina);
    print_person(tina);

    delete_person(tommy);
    delete_person(tina);
    return 0;
}

Person *
create_person(char *name, int age, int height)
{
    Person *who = malloc(sizeof(Person));
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    return who;
}

void
delete_person(Person *person)
{
    free(person->name);
    free(person);
}

void
years_later(Person *person, int years)
{
    person->age += years;
    person->height += years * 2;

}

void
print_person(Person *person)
{
    printf("Name: %s\n", person->name);
    printf("\tage: %d\n", person->age);
    printf("\theight: %d\n", person->height);
}

