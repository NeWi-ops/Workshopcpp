# Mini-rapport de Workshop Iwen Martin

## Voici les avant-après des images traités durant les exercices. Certaines sont accompagnées des difficultées rencontrées mais toutes les explications sont dans le main pour chaque étape de code.



### **Ne garder que le vert**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/KeepGreenOnly.png)


### **Échanger les canaux**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/SwapColors.png)


### **Noir & Blanc**

- Avant :
![Image avant effet](images/logo.png)
- Bug :
![Image après un problème](output/BlackAndWhiteBug.png)
- Après :
![Image après effet](output/BlackAndWhite.png)

Ici j'ai eu un soucis car j'ai rajouté une ligne de code en trop qui faisait que si le pixel tendait plus vers le noir que le blanc on le colorait en noir et inversement. Cela donne cependant une image interressante. En otant cette ligne là on obtient bien une image en nuance de gris.


### **Négatif**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/Negative.png)


### **Dégradé**

Ici on a pas d'image de base on créé directement une image noire sur laquelle on va agir.
![Image après effet](output/Gradient.png)


### **Miroir**

- Avant :
![Image avant effet](images/logo.png)
Il y a eu plusieurs fois le même problême mais qui a agit de manière différentes pour cet exercice là.
Pour la première tentative j'ai échangé tous les pixels de position selon x ET y mais en dépassant la moitié de l'image cela ne change plus rien.
- Bug 1:
![Image premier bug](output/MirrorBug.png)

ensuite j'ai le même soucis puisque j'ai simplement retiré la partie qui échangeait les y de position. La moitié gauche de l'image ne suit toujours aucun changement.
- Bug 2:
![Image deuxième bug](output/MirrorBug2.png)

Cette fois ci on utilise ici swap qui permet d'échanger de position les pixels directement et qui résout donc le problème qui faisait que l'on traitait des pixels qui avaient déjà changé de position.
- Après :
![Image après effet](output/Mirror.png)


### **Image bruitée**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/Noise.png)


### **Rotation de 90°**

Le seul soucis que j'ai eu ici était pour comprendre comment tourner du bon coté mais cela dépend de si on agit sur la height ou la width.
- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/Rotation.png)


### **RGB split**

ma difficulté ici a été de correctement séparer en 3 if afin d'avoir le plus bel effet possible. Car en mettant toute les translations de couleurs dans le même if l'effet nétait pas présent sur les bords de l'image (en effet j'ai fait en sorte qu'un pixel ne puisse pas dépasser de l'image si il était déplacé)
- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/RGBsplit.png)


### **Luminosité**

- Avant :
![Image avant effet](images/photo.jpg)
- Après :
![Image après effet](output/Brightness.jpg)


### **Disque**


On part d'une image noire
![Image après effet](output/Disk.png)


### **Cercle**

On part d'une image noire

![Image après effet](output/Circle.png)


### **Animation**

Ici j'ai eu un soucis car j'avais oublié de delete les pixels colorés en blanc entre chaque frame de l'animation. Pour 100 frame j'obtenais donc ce résultat :
![Animation après un problème](output/AnimationBug.gif)

En rendant l'image noir avant chaque génération de nouveau disque j'obtiens le résultat escompté. Pour 30 frame on a : 
![Animation](output/Animation.gif)


### **Rosace**

J'avais ici tout simplement oublié de générer des cercles j'avais donc de tout petits disques mais qui avaient le bon angle de rotation.
![Image bug](output/RosaceBug.png)

j'ai résolu le probleme ensuite mais j'ai deux fonctions. Une où tout le code est détaillé mais qui n'a pas de paramètre qui agissent sur les cercles et donc ne permet pas de manipuler les dimensions de la rosace et un autre qui réutilise la fonction Circle et permet alors d'agi sur certains paramètre de la Rosace.
![Image après effet](output/RosaceCircle.png)


### **Mosaïque**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/Mosaique.png)


### **Mosaïque miroir**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/MirrorMosaique.png)


### **Glitch**

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/Glitch.png)


### **Tri de pixels**
J'ai commencé par tester la fonction sort:
![Image Test](output/PixelSortTest.png)
j'ai ensuite appliqué l'effet :

- Avant :
![Image avant effet](images/logo.png)
- Après :
![Image après effet](output/PixelSort.png)


### **Dégradés dans l'espace de couleur Lab**

On réalise un premier dégradé dans l'espace RGB : 
![Image après effet](output/SpaceGradient.png)

Puis on le transpose dans l'espace Lab :
![Image après effet](output/SpaceGradientOklab.png)


### **Fractale de Mandelbrot**

On part d'une image noir à la base et on obtient ceci :
![Image après effet](output/MandelbrotFractal.png)


### **Normalisation de l'histogramme**

- Avant :
![Image avant effet](images/photo_faible_contraste.jpg)
- Après :
![Image après effet](output/Normalisation.jpg)


### **Vortex**
image de base : ![Image avant effet](images/logo.png)

J'ai eu plusieurs soucis avec la premiere tentative. Des points qui avaient subis une rotation en subissaient à nouveau une et ceux qui n'en subissait car sinon ils sortaient de l'image restaient à leur place et on les voyait en arrière plan : 

![Image bug](output/VortexBug.png)

J'ai trouvé une parade mais qui ne résolvait le problème qu'en surface en rendant noir les pixels qui ne changeaient pas de place : 

![Image bug](output/VortexV1.png)

En crééant une nouvelle image et en copiant les pixels apres rotation dedans on résout tous les soucis : 

![Image après effet](output/Vortex.png)












































