# philo
sujet: https://cdn.intra.42.fr/pdf/pdf/31024/en.subject.pdf
## Threads:

Un **thread***(Fil ou encore Fil d'exécution)* est une portion de code *(fonction)* qui se déroule en parallèle au thread principal (aussi appelé *main*). Ce principe est un peu semblable à la fonction **[fork](https://man.developpez.com/man2/fork.2.php)** sur Linux par exemple sauf que nous ne faisons pas de copie du processus père, nous définissons des fonctions qui vont se lancer en même temps que le processus, ce qui permet de faire de la programmation multitâche. Le but est donc de permettre au programme de réaliser plusieurs actions au même moment (imaginez un programme qui fait un gros calcul et une barre de progression qui avance en même temps).On peut également considérer un thread comme un processus allégé pour mieux imager le tout ! En comparaison des threads, un fork prend en moyenne 30 fois plus de temps à faire !

- **pthread_create:**
    
    `int pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);`
    
    1. Le type pthread_t correspond à l'identifiant du thread qui sera créé, tout comme les processus ont leur propre identifiant.
    2. Le type pthread_attr_t est un autre type opaque permettant de définir des attributs spécifiques pour chaque thread.
    3. Chaque thread dispose d'une fonction à exécuter, c'est en même temps sa raison de vivre… Cet argument permet de transmettre un pointeur sur la fonction qu'il devra exécuter.
    4. Ce dernier argument représente un argument que l'on peut passer à la fonction que le thread doit exécuter.
    
    Si la création réussit, la fonction renvoie 0(zéro) et l'identifiant du thread nouvellement créé est stocké à l'adresse fournie en premier argument.
    
    mise en pratique : [https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
    

## Mutex :

Les mutex sont un système de verrou donnant ainsi une garantie sur la viabilité des données manipulées par les threads. En effet, il arrive même très souvent que plusieurs threads doivent accéder en lecture et/ou en écriture aux mêmes variables. Si un thread possède le verrou, seulement celui-ci peut lire et écrire sur les variables étant dans la portion de code protégée (aussi appelée zone critique). Lorsque le thread a terminé, il libère le verrou et un autre thread peut le prendre à son tour.

### Pour créer un mutex, il faut tout simplement déclarer une variable du type `pthread_mutex_t` et l'initialiser

1.  `pthread_mutex_t	mutex;`
2. `pthread_mutex_init(mutex, NULL);`

### Un mutex n'a que deux états possibles, il est soit verrouillé, soit déverrouillé. On utilise les deux fonctions ci-dessous pour changer les états.

1. `int pthread_mutex_lock (pthread_mutex_t * mutex);`
2. `int pthread_mutex_unlock (pthread_mutex_t * mutex);`

Les deux fonctions prennent en argument l'adresse d'un mutex de type pthread_mutex_t. 

Les deux fonctions renvoient 0 en cas de succès ou l'une des valeurs suivantes en cas d'échec :

- **EINVAL :** mutex non initialisé ;
- **EPERM :** le thread n'a pas la main sur le mutex.
