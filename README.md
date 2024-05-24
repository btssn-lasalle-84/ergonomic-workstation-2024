![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=plastic) ![Raspberry Pi Badge](https://img.shields.io/badge/Raspberry%20Pi-A22846?logo=raspberrypi&logoColor=fff&style=plastic)

[![qt-build](https://github.com/btssn-lasalle-84/ergonomic-workstation-2024/actions/workflows/make-qt.yml/badge.svg)](https://github.com/btssn-lasalle-84/ergonomic-workstation-2024/actions/workflows/make-qt.yml) [![pages-build-deployment](https://github.com/btssn-lasalle-84/ergonomic-workstation-2024/actions/workflows/pages/pages-build-deployment/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/ergonomic-workstation-2024/actions/workflows/pages/pages-build-deployment)

# Le projet ergonomic-workstation 2024

- [Le projet ergonomic-workstation 2024](#le-projet-ergonomic-workstation-2024)
  - [Présentation](#présentation)
  - [Fonctionnalités](#fonctionnalités)
  - [Documentation du code](#documentation-du-code)
  - [Diagramme de classes](#diagramme-de-classes)
  - [Protocole](#protocole)
  - [Screenshots](#screenshots)
  - [Historique des versions](#historique-des-versions)
  - [Auteurs](#auteurs)

---

## Présentation

Il s'agit de digitaliser un poste de travail afin de guider l’opérateur pas à pas dans la réalisation d’un processus d’assemblage.

![](images/ergonomic-workstation.png)

## Fonctionnalités

![](images/uc.png)

La table ergonomique devra être capable de proposer plusieurs processus d'assemblage et d'accompagner l'opérateur durant le  processus d'assemblage.

|Tâche|Priorité|Itération|
|-----|:------:|:-------:|
|Séquences les opérations|H|2|
|Visualiser les statistique de production|B|3|
|Visualiser tous les processus d’assemblage|H|1|
|Arrêter le système à tout moment|M|3|
|Choisir un opérateur|B|3|
|Détecter une erreur|M|2|
|Choisir le processus d’assemblage|M|2|
|Communiquer avec le poste de travail (liaison série)|M|2|

## Documentation du code

https://btssn-lasalle-84.github.io/ergonomic-workstation-2024/

## Diagramme de classes

![](images/classes-v0.2.png)

## Protocole

Format : `$[TYPE];[DONNEE]\n`

Type de trame : `‘E’` (encodeur)

Donnée :

- `‘1’` pour droite
- `‘2’` pour gauche
- `‘3’` pour validation

Exemples :

- `$E;2\n` l'encodeur a été” déplacé d’un “cran” vers la gauche 
- `$E;3\n` appui sur l’encodeur

## Screenshots

![](images/screenshot-v0.2.gif)

## Historique des versions

- Version 0.2

![](images/jira-v0.2.png)

- Version 0.1

![](images/jira-v0.1.png)

## Auteurs

- Étudiant IR : AVRIL Gabain <<gabain.avril@gmail.com>>

---
©️ LaSalle Avignon 2024
