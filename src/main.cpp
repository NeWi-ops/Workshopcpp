#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include "random.hpp"
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>




void KeepGreenOnly (sil::Image& image)
{
    //Parcourir tous les pixels de l'image
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x, y).r = 0.f;
        image.pixel(x,y).b = 0.f;    // Passe sur chaque pixels pour retirer le rouge et le bleu
    }
}
}



void SwapColors (sil::Image& image)
{
    //Parcourir tous les pixels de l'image
    for (glm::vec3& color : image.pixels())
    {
        //Inverser les positions des pixels de couleur bleu avec ceux de couleur rouge
        color = glm::vec3 (color.b, color.g, color.r);
    }

}


void BlackAndWhiteBug (sil::Image& image) 
{
    //Parcourir tous les pixels de l'image
    for (glm::vec3& color : image.pixels())
    {
    //Définir la variable qui permet de convertir les couleurs en nuances de gris
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    gray = (gray > 0.5f) ? 1.0f : 0.0f; //Ligne non nécessaire ne donne pas l'effet escompté
    //réassigner le gris défini aux pixels de l'image
    color = glm::vec3{gray};
    }
}

void BlackAndWhite (sil::Image& image) 
{
    //Parcourir tous les pixels de l'image
    for (glm::vec3& color : image.pixels())
    {
    //Définir la variable qui permet de convertir les couleurs en nuances de gris
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    //réassigner le gris défini aux pixels de l'image
    color = glm::vec3{gray};
    }
}

void Negative (sil::Image& image)
{
    //Parcourir tous les pixels de l'image
    for (glm::vec3& color : image.pixels())
    {
        //changer la couleur par son inverse 
        color = glm::vec3 (1-color.b, 1-color.g, 1-color.r);
    }
}

sil::Image Gradient ()
{
    //créer une nouvelle image noire
    sil::Image image{300, 200};
    //parcourir tous les pixels de l'image
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            //On divise la position selon les x de chaque pixel par la largeur de l'image afin d'obtenir une nuance plus ou moins noir(ou blanche)
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }    
    return image;
}

void MirrorBug (sil::Image& image)
{
    //parcourir tous les pixels de l'image 
    for (int x{0}; x < (image.width())/2; x++)
    {
    for (int y{0}; y < image.height(); y++)
    {
        //Probleme : ici on échange tous les pixels de position selon x ET y mais en dépassant la moitié de l'image cela ne change plus rien
        image.pixel(x,y)=image.pixel(image.width()-1-x,image.height()-1-y);
    }
}
}

void MirrorBug2 (sil::Image& image)
{
    //parcourir tous les pixels de l'image 
    for (int x{0}; x < (image.width()); x++)
    {
    for (int y{0}; y < image.height(); y++)
    {
        //Probleme : ici on échange tous les pixels de position selon x mais en dépassant la moitié de l'image cela ne change plus rien
        image.pixel(x,y)=image.pixel(image.width()-1-x,y);
    }
    }
}

void Mirror (sil::Image& image)
{
    //parcourir uniquement la moitié de gauche des pixels de l'image pour ne pas les rééchanger de positions
    for (int x{0}; x < (image.width()/2); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //on utilise ici swap qui permet d'échanger de position les pixels directement.
            std::swap(image.pixel(x,y),image.pixel((image.width())-1-x,y));
        }
    }
}

void Noise (sil::Image& image)
{
    int width {image.width()};
    int height {image.height()};
    //on défini le nombre de pixels aléatoire dont on souhaite changer la couleur
    for (int i{}; i<50000; i++)
    {
        //on choisit les pixels de manière aléatoire
        int x = std::rand() % width;   
        int y = std::rand() % height;

        //on choisit ensuite une valeur aléatoire entre 0 et 1 pour chaque couleur RGB afin d'obtenir un pixel de couleur aléatoire 
        float r = static_cast<float>(std::rand()) / RAND_MAX;
        float g = static_cast<float>(std::rand()) / RAND_MAX;
        float b = static_cast<float>(std::rand()) / RAND_MAX;

        //on assigne ensuite cette couleur au pixel 
        image.pixel(x,y).r = r;
        image.pixel(x,y).g = g;
        image.pixel(x,y).b = b;
    }
}

void Rotation (sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    //on créer une nouvelle image en attribuant la largeur de celle de base pour la taille et inversement 
    sil::Image rotatedImage(height, width);
    //on parcourt tous les pixels l'image de base
    for (int x = 0; x < width; x++) 
    {
        for (int y = 0; y < height; y++) 
        {
            //on attribue à l'image créée le pixel correspondant à une rotation de 90 degrés dans le sens antihoraire
            rotatedImage.pixel(height - 1 - y, x)=image.pixel(x,y);
        }
    }
    //l'image de base devient la nouvelle
    image = rotatedImage;
}

void RGBsplit (sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    //on créé une nouvelle image noire de même taille que celle de base
    sil::Image splitimage(width, height);
    //on parcourt tous les pixels de celle-ci
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            //on décale le bleu de chaque pixel dont la position est supérieur à 30 vers la gauche en veillant à ne pas les sortir de l'image
            if (x>30)
            {
                splitimage.pixel(x,y).b=image.pixel(x-30,y).b;
            }
            else
            {
                splitimage.pixel(x,y).b=image.pixel(x,y).b;
            }
            //on décale le bleu de chaque pixel dont la position est supérieur à width-30 vers la droite en veillant à ne pas les sortir de l'image
            if (x<width-30)
            {
                splitimage.pixel(x,y).r=image.pixel(x+30,y).r;
            }
            else
            {
                splitimage.pixel(x,y).r=image.pixel(x,y).r;
            }
            //on conserve la position du vert de chaque pixel
            splitimage.pixel(x,y).g=image.pixel(x,y).g;
        
        }
    }
    //l'image de base devient la nouvelle
    image = splitimage;
}

void Brightness (sil::Image& image, float p)
{
    int width = image.width();
    int height = image.height();

    //on parcourt tous les pixels de l'image
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            

            //en utilisant la fonction puissance on élève plus ou moins la luminosité de chaque pixel selon sa position. l'exposant est un argument de la fonction brightness.
            image.pixel(x,y).r = std::pow(image.pixel(x,y).r, p);   
            image.pixel(x,y).g = std::pow(image.pixel(x,y).g, p);   
            image.pixel(x,y).b = std::pow(image.pixel(x,y).b, p);   

            
            
        }
    }
}

sil::Image Disk ()
{
    //on génère une image noire
    sil::Image image{500, 500};

    //on défini le centre du disque son rayon au carré
    int width = image.width();
    int height = image.height();
    int centerX {250};
    int centerY {250};
    int radius {10000};
    //on parcourt tous les pixels de l'image
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            //on défini la distance au carré entre le centre et chaque pixel de l'image
            int dx {x - centerX};
            int dy {y - centerY};
            int distanceSquared {dx * dx + dy * dy};

            //si cette distance au carré est inférieur au rayon au carré du disque alors on colorie le pixel concerné en blanc
            if (distanceSquared<radius)
            {
                image.pixel(x,y)=glm::vec3{1, 1, 1};
            }
        }
    }
    return image;
}



sil::Image Circle(sil::Image& image, int centerX, int centerY, int radius, int thickness)
{
    
    int height{image.height()};
    int width{image.width()};
    //on parcourt tous les pixels de l'image
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            //tout comme le disque on défini la distance entre chaque point parcouru et le centre du cercle
            int dx = x - centerX;
            int dy = y - centerY;
            int distance = static_cast<int>(std::sqrt(dx * dx + dy * dy));

            //on prend en compte l'épaisseur du tracé du cercle, les seuls pixels colorés seront ceux dont la distance est supérieur au rayon mais inférieur au rayon + l'épaisseur
            if (distance >= radius && distance <= radius + thickness) 
            {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f);  
            }
        }
    }
    return image;
}

sil::Image Animation ()
{
    //on créé une nouvelle image
    sil::Image image{500, 500};
    int width = image.width();
    int height = image.height();
    //on place le centre du disque qui va se déplacer au niveau de la moitié de l'image (dans le sens des y)
    int centerX {};
    int centerY {250};
    int radius {10000};
    for (int i {0}; i<30; i++)
    {
        //à chaque répétition on repart d'une image noire pour éviter d'avoir la même chose que dans le "output/Animationbug.png"
        sil::Image image{500, 500};
        //on parcourt chaque pixels de l'image
        for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x) 
            {
                //on répète le code utilisé pour le disque 
                int dx {x - centerX};
                int dy {y - centerY};
                int distanceSquared {dx * dx + dy * dy};

                if (distanceSquared<radius)
                {
                    image.pixel(x,y)=glm::vec3{1, 1, 1};
                }
            }
            
        }
        //on déplace le centre de chque disque créé afin de faire en sorte qu'il se "déplace"
        centerX += width/30;
        image.save("output/animation/diskframe"+std::to_string(i)+".png");
    }    
    
    return image;
}

sil::Image RosaceBug()
{
    //on créé une nouvelle image noire
    sil::Image image{500, 500};
    int height {image.height()};
    int width {image.width()};
    //on défini un cercle qui sera le cercle central de la rosace
    int radius {100};
    int centerX {250};
    int centerY {250};
    int thickness{5};
    //on veut une rosace à 7 cercles donc il en reste 6 à dessiner 
    for (int i{0}; i<6; i++)
    {
        //on déplace le centre de chaque cercles d'un angle de 2pi/6 
        centerX = 250 + (radius*cos((2*i*M_PI)/6));
        centerY = 250 + (radius*sin((2*i*M_PI)/6));
        //on dessine chaque cercle
        for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x) 
            {
                int dx {x - centerX};
                int dy {y - centerY};
                int distanceSquared {dx * dx + dy * dy};
                //ici j'ai fait une erreur en oubliant l'épaisseur donc je dessine des disques et non des cercles ce qui ne nous renverra pas une rosace
                if (distanceSquared<radius)
                {
                    image.pixel(x,y)=glm::vec3{1, 1, 1};
                }
            }
        }
    }
    return image;
}

sil::Image Rosace()
{
    //On a ici la même fonction que précédemment mais avec la bonne partie de code pour dessiner les cercles
    sil::Image image{500, 500};
    int height {image.height()};
    int width {image.width()};
    int radius {100};
    int centerX {250};
    int centerY {250};
    int thickness{3};
    for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x) 
            {
                int dx {x - centerX};
                int dy {y - centerY};
                int distance = static_cast<int>(std::sqrt(dx * dx + dy * dy));

                if (distance >= radius && distance <= radius + thickness)
                {
                    image.pixel(x,y)=glm::vec3{1, 1, 1};
                }
            }
        }

    for (int i{0}; i<6; i++)
    {
        centerX = 250 + (radius*cos((2*i*M_PI)/6));
        centerY = 250 + (radius*sin((2*i*M_PI)/6));
        for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x) 
            {
                int dx {x - centerX};
                int dy {y - centerY};
                int distance = static_cast<int>(std::sqrt(dx * dx + dy * dy));

                if (distance >= radius && distance <= radius + thickness)
                {
                    image.pixel(x,y)=glm::vec3{1, 1, 1};
                }
            }
        }
    }
    return image;
}

sil::Image RosaceCircle(sil::Image image, int centerX, int centerY, int radius, int thickness)
{
    //Pour se simplifier la tache on peut également réutiliser la fonction Circle que l'on avait fait plus haut
    //on dessine alors ici le premier cercle (le central)
    Circle(image, centerX, centerY, radius, thickness);
    //puis on dessine 6 cercles autour dont le centre est décalé d'un angle 2pi/6 entre chaque cercles
    for (int i{0}; i<6; i++)
    {
        centerX = 250 + (radius*cos((2*i*M_PI)/6));
        centerY = 250 + (radius*sin((2*i*M_PI)/6));
        Circle(image, centerX, centerY, radius, thickness);
    }
    return image;
}



void Mosaique(sil::Image& image, int nombre)
{
    //On créé une nouvelle image aux même dimensions que celle de base
    sil::Image Mosa{image.width(), image.height()};
    //on parcourt tous les pixels de l'image
    for (int y = 0; y < image.height(); ++y) 
        {
            for (int x = 0; x < image.width(); ++x) 
            {
                //ici on définit la largeur et la hauteur de chaque bloc de la mosaique et avec le modulo on calcul la position relative d'un pixel de l'image de base dans le bloc
                int x2 {x%(image.width()/nombre)};
                int y2 {y%(image.height()/nombre)};
                //ici on copie les pixels de l'image de base dans chaque bloc de Mosa
                Mosa.pixel(x,y)=image.pixel(x2*nombre,y2*nombre);
            }
        }
        image = Mosa;
}

void MirrorMosaique(sil::Image& image, int nombre)
{
    //on a ici le même début que pour la fonction mosaique
    sil::Image Mosa(image.width(), image.height());

    int width = image.width() / nombre;
    int height = image.height() / nombre;

    for (int y = 0; y < image.height(); ++y) 
    {
        for (int x = 0; x < image.width(); ++x) 
        {
            
            int x2 = x % width;
            int y2 = y % height;

            //On inverse les coordonnées des x si la colonne est impaire
            if ((x / width)%2==1) 
            {  
                x2 = width - 1 - x2;  
            }
            //On inverse les coordonnées des y si la ligne est paire
            if ((y/height)%2 == 0)
            {
                y2 = height - 1 - y2;
            }

            // Copier le pixel de l'image source
            Mosa.pixel(x, y) = image.pixel(x2 * nombre, y2 * nombre);
        }
    }
    image=Mosa;
}



void Glitch(sil::Image &image)
{
    

    int width = image.width();
    int height = image.height();

    //On définit le nombre de répétitions d'échange de positions de rectangles dans l'image
    for (int i{}; i<50; i++)
    {

    
        //On définit une taille semi-aléatoire pour chaque rectangle
        int rectWidth = random_int(20, 40);
        int rectHeight = random_int(2, 10);
        
        

        //on définit 2 int qui permettront de vérifier que les rectangles ne sortent pas de l'image
        int maxX = width - rectWidth;
        int maxY = height - rectHeight;

    


        // Choisir des positions aléatoires pour les rectangles en utilisant le modulo pour ne pas avoir des coordonnées en dehors de l'image
        int x1 = std::rand() % maxX;
        int y1 = std::rand() % maxY;
        int x2 = std::rand() % maxX;
        int y2 = std::rand() % maxY;

        //on copie les pixels du premier rectangle 
        sil::Image rect1(rectWidth, rectHeight);
        for (int i = 0; i < rectHeight; ++i) {
            for (int j = 0; j < rectWidth; ++j) {
                rect1.pixel(j, i) = image.pixel(x1 + j, y1 + i);
            }
        }

        //on copie les pixels du second rectangle 
        sil::Image rect2(rectWidth, rectHeight);
        for (int i = 0; i < rectHeight; ++i) {
            for (int j = 0; j < rectWidth; ++j) {
                rect2.pixel(j, i) = image.pixel(x2 + j, y2 + i);
            }
        }

        // On échange ensuite les pixels des rectangles copiés précedemment
        for (int i = 0; i < rectHeight; ++i) {
            for (int j = 0; j < rectWidth; ++j) {
                // Remplacer le premier rectangle par le deuxième
                image.pixel(x1 + j, y1 + i) = rect2.pixel(j, i);

                // Remplacer le second rectangle par le premier
                image.pixel(x2 + j, y2 + i) = rect1.pixel(j, i);
            }
        }
    }
}

void PixelSortTest(sil::Image& image)
{
     
    //J'ai chercher à voir comment fonctionnait la fonction sort
    std::sort(image.pixels().begin(), image.pixels().end(), [](const glm::vec3& color1, const glm::vec3& color2) {
        return glm::length(color1) < glm::length(color2);
    });
}

void PixelSort(sil::Image& image)
{
    int width = image.width();
    int height = image.height();
   
    // on parcourt chaque ligne une a une dans l'image
    for (int y = 0; y < height; ++y) 
    { 
        //on initialise x 
        int x = 0; 
        //on boucle sur x en s'assurant que x ne dépasse pas la largeur de l'image
        while (x < width) 
        {
            //on définit ensuite l'espacement aléatoire qu'il y aura entre chaque fragment de ligne triés
            int espacement = random_int(0, 100); 
            //on ajoute cet espacement à x en vérifiant à nouveau qu'il ne sorte pas de l'image
            x += espacement;
            if (x >= width) break;
            //ici on définit la longueur de chaque fragment de ligne de pixels triés
            int longueur = random_int(30, 50);
            //ici on définit la variable qui va permettre d'arreter le tri si celui ci dépasse de l'image
            int end = std::min(x + longueur, width);

            //on utilise la fonction sort afin de trier des fragments de lignes selon la luminosité de chaque pixels
            std::sort(image.pixels().begin() + y * width + x, image.pixels().begin() + y * width + end,    
                [](const glm::vec3& color1, const glm::vec3& color2) 
                {
                    return glm::length(color1) < glm::length(color2);
                });
            //on assigne la nouvelle valeur à x afin de recommencer la boucle. lorsque x aura atteint le bord de l'image on traitera la ligne suivante
            x = end;
        }
    }
}

sil::Image SpaceGradient()
{
    //on définit une nouvelle image noire
    sil::Image image{500,500};

    glm::vec3 color1(1.0f, 0.0f, 0.0f);  // Rouge
    glm::vec3 color2(0.0f, 0.0f, 1.0f);  // Bleu

    int width = image.width();
    int height = image.height();

    // On va appliquer le dégradé sur chaque pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // on calcule le facteur de mélange en fonction de la position du pixel
            float mixFactor = static_cast<float>(x) / width;

            // on mélange ensuite les deux couleurs en fonction du facteur de mélange
            glm::vec3 mixedColor = (glm::mix((color1), (color2), mixFactor));


            // Assigner la couleur au pixel de l'image
            image.pixel(x, y) = mixedColor;
        }
    }
    return image;
}

// Ici on a les fonctions qui permettent de passer du RGB au OKlab et inversement
struct Lab {float L; float a; float b;};
struct RGB {float r; float g; float b;};

glm::vec3 lab(glm::vec3 c) 
{
    float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
	float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}

glm::vec3 rgb(glm::vec3 c) 
{
    float l_ = c.x + 0.3963377774f * c.y + 0.2158037573f * c.z;
    float m_ = c.x - 0.1055613458f * c.y - 0.0638541728f * c.z;
    float s_ = c.x - 0.0894841775f * c.y - 1.2914855480f * c.z;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

sil::Image SpaceGradientOklab()
{
    //on utilise le même code que pour la fonction Gradient précedente
    sil::Image image{500, 500};
    glm::vec3 color1(1.0f, 0.0f, 0.0f);  
    glm::vec3 color2(0.0f, 0.0f, 1.0f);  

    int width = image.width();
    int height = image.height();

    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            float mixFactor = static_cast<float>(x) / width;

            //cette fois ci on utilise les fonctions données pour passer les couleurs du dégradé en OKlab
            glm::vec3 mixedColor = rgb(glm::mix(lab(color1), lab(color2), mixFactor));
            //on assigne les nouvelles couleurs aux pixels de l'image
            image.pixel(x, y) = mixedColor;
        }
    }
    
    return image;
    
}

sil::Image MandelbrotFractal()
{
    //on définit une nouvelle image
    sil::Image image{2000,2000};
    int width = image.width();
    int height = image.height();
    //On définit le maximum d'itteration offert à z pour atteindre 2
    int MaxIteration {1000};
    //on parcourt tous les pixels de l'image
    for (int x = 0; x<width; x++)
    {
        for (int y = 0; y<height; y++)
        {
            //on commence par contenir la partie réelle a et la partie imaginaire b dans un intervalle [-2,2]
            double a {(static_cast<double>(x)/width)*4.0-2.0};
            double b {(static_cast<double>(y)/width)*4.0-2.0};
            //on définit le nombre complexe c avec a et b et on initialise z
            std::complex<double> c(a, b);
            std::complex<double> z(0, 0);

            int iteration{0};
            //on boucle tant que z est inférieur à 2 et que le nombre d'itteration est inférieur au maximum
            while(iteration<MaxIteration && std::abs(z)<=2.0)
            {
                z = z * z + c;
                iteration+=1;
            }
            //on colorie le pixel en rouge si le nombre maximum d'iterration est atteint
            if (iteration==MaxIteration)
            {
                image.pixel(x,y) = glm::vec3(1.0f,0.0f,0.0f);

            }
            //ici on colorie le pixel avec une nuance de rouge qui va dépendre du nombre d'iterration avant que z dépasse 2
            else 
            {
                
                float red = static_cast<float>(iteration) / (30);
                image.pixel(x, y) = glm::vec3(red, 0.0f, 0.0f); 
            }
            
        }
    }
    return image;
}

void Dithering(sil::Image image)
{
    int width {image.width()};
    int height {image.height()};


}
//on a ici la fonction qui va permettre d'offrir une rotation au pixel
glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void VortexBug(sil::Image& image)
{

    int width = image.width();
    int height = image.height();
    //on définit l'angle maximum qu'un pixel pourra avoir (à savoir si le pixel est le plus éloigné de tous du centre)
    double maxangle = 8*M_PI;
    //on définit le centre de la rotation
    glm::vec2 CenterRotation(width/2, height/2);
    //on parcourt tous les pixels de l'image
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            //pour chaque points on calcule sa distance par rapport au centre de rotation et on définit l'angle selon lequel chaque pixel va se déplacer et qui dépend de cette distance
            glm::vec2 point(x, y);
            float distance = glm::distance(point, CenterRotation);
            float angle = maxangle * (distance / std::max(width, height));
            //on fait tourner ce pixel que l'on garde dans une variable
            glm::vec2 rotatedPoint = rotated(point, CenterRotation, angle);

            //si le pixel ne sort pas de l'image on remplace le pixel original par celui qui est à sa position apres avoir subit une rotation
            //le probleme ici est qu'un pixel ayant déja subit une rotation pourra être utilisé pour un définir un autre pixel
            //De plus n'ayant pas défini une nouvelle image auparavant pour y mettre les pixels subissant une rotation les pixels n'en ayant pas subit restent en place donc on a toujours certaines parties de l'image d'origine derrière le vortex
            if (rotatedPoint.x >= 0 && rotatedPoint.x < width && rotatedPoint.y >= 0 && rotatedPoint.y < height) 
            {
                image.pixel(x, y) = image.pixel(static_cast<int>(rotatedPoint.x), static_cast<int>(rotatedPoint.y));
            }
        }
    }


}

void VortexV1(sil::Image& image)
{
    //on a ici le même code que précedemment
    int width = image.width();
    int height = image.height();
    double maxangle = 10*M_PI;
    glm::vec2 CenterRotation(width/2, height/2);

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            glm::vec2 point(x, y);
            float distance = glm::distance(point, CenterRotation);
            float angle = maxangle * (distance / std::max(width, height));
            glm::vec2 rotatedPoint = rotated(point, CenterRotation, angle);

            if (rotatedPoint.x >= 0 && rotatedPoint.x < width && rotatedPoint.y >= 0 && rotatedPoint.y < height) 
            {
                image.pixel(x, y) = image.pixel(static_cast<int>(rotatedPoint.x), static_cast<int>(rotatedPoint.y));
            }
            else
            {
                //on cherche à résoudre un des problemes qui nous faisait face mais c'est seulement une résolution en surface qui rend noir les pixels n'ayant pas bougés
                glm::vec3 black(0.0f, 0.0f, 0.0f);
                image.pixel(x,y) = black;
            }
        }
    }
}



void Vortex(sil::Image& image)
{
    //On a le même principe que pour les versions du vortex précédentes mais ici on créé une nouvelle image pour y copier les pixels ayant subit une rotation 
    sil::Image Vortex{image.width(),image.height()};
    int Vwidth = Vortex.width();
    int Vheight = Vortex.height();
    int Iwidth = image.width();
    int Iheight = image.height();
    double maxangle = 25*M_PI;
    glm::vec2 CenterRotation(Iwidth/2, Iheight/2);

    for (int y = 0; y < Iheight; ++y) 
    {
        for (int x = 0; x < Iwidth; ++x) 
        {
            glm::vec2 point(x, y);
            float distance = glm::distance(point, CenterRotation);
            float angle = maxangle * (distance / std::max(Iwidth, Iheight));
            glm::vec2 rotatedPoint = rotated(point, CenterRotation, angle);
            //on a résolu les deux problèmes
            if (rotatedPoint.x >= 0 && rotatedPoint.x < Vwidth && rotatedPoint.y >= 0 && rotatedPoint.y < Vheight) 
            {
                
                Vortex.pixel(x, y) = image.pixel(static_cast<int>(rotatedPoint.x), static_cast<int>(rotatedPoint.y));
            }
            
        }
    }
    image = Vortex;

}

void Normalisation(sil::Image& image)
{
    int width {image.width()};
    int height {image.height()};
    //on définit une nouvelle image 
    sil::Image normalisation{width,height};
    //on définit deux int qui permettront de comparer la luminosité de tous les pixels de l'image
    float minLumi{1.0f};
    float maxLumi{0.0f};
    //on parcourt tous les pixels de l'image
    for (const glm::vec3& color : image.pixels())
    {
        //on défini Lumi qui permet d'obtenir les nuances de gris d'un pixel et donc sa luminosité
        float Lumi = 0.3f * color.r + 0.59f * color.g + 0.11f * color.b;
        //on cherche ensuite le pixel le moins lumineux et le pixel le plus lumineux
        minLumi = std::min(minLumi, Lumi);
        maxLumi = std::max(maxLumi, Lumi);
    }
    // on parcourt à nouveau tous les pixels de l'image
    for (glm::vec3& color : image.pixels())
    {
        //on normalise alors la luminosité de chaque pixel en fonction du minimum et du maximum que l'on a trouvé précédemment
        float luminance = 0.3f * color.r + 0.59f * color.g + 0.11f * color.b;
        float NormalLumi = (luminance - minLumi) / (maxLumi - minLumi);
        //on change les niveaux de couleurs des pixels
        color = color * NormalLumi/luminance ;
    }
}






int main()
{
    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     KeepGreenOnly (image);
    //     image.save("output/KeepGreenOnly.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     SwapColors (image);
    //     image.save("output/SwapColors.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     BlackAndWhiteBug (image);
    //     image.save("output/BlackAndWhiteBug.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     BlackAndWhite (image);
    //     image.save("output/BlackAndWhite.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     Negative (image);
    //     image.save("output/Negative.png");
    // }

    // {
        
    //     sil::Image image {Gradient()};
    //     image.save("output/Gradient.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         MirrorBug (image);
    //         image.save("output/MirrorBug.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         MirrorBug2 (image);
    //         image.save("output/MirrorBug2.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         Mirror (image);
    //         image.save("output/Mirror.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         Noise (image);
    //         image.save("output/Noise.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         Rotation (image);
    //         image.save("output/Rotation.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //         // TODO: modifier l'image
    //         RGBsplit (image);
    //         image.save("output/RGBsplit.png");
    // }
   
    // {
    //     sil::Image image{"images/photo.jpg"};
    //         // TODO: modifier l'image
    //         //std::cout<< "Entrez une valeur entre 0 et 1 pour éclaircir et supérieur à 1 pour assombrir"<<std::endl;
    //         //float p {};
    //         //std::cin>>p;
    //         Brightness (image,2);
    //         image.save("output/Brightness.jpg");
    // }

    // {
    //     sil::Image image{Disk()};
    //         // TODO: modifier l'image
    //         image.save("output/Disk.png");
    // }

    // {
    //     sil::Image IMAGE{500,500};
    //     sil::Image image{Circle(IMAGE, 250, 250, 100, 3)};
        
    //         // TODO: modifier l'image
    //         image.save("output/Circle.png");
    // }

    // {
    //    sil::Image image{Animation()};
    //         // TODO: modifier l'image
            
    // }

    // {
    //     sil::Image image{RosaceBug()};
        
    //         // TODO: modifier l'image
    //         image.save("output/RosaceBug.png");
    // }

    // {
    //     sil::Image image{Rosace()};
        
    //         // TODO: modifier l'image
    //         image.save("output/Rosace.png");
    // }

    // {
    //     sil::Image IMAGE{500, 500};
    //     sil::Image image{RosaceCircle(IMAGE, 250, 250, 100, 3)};
    //     image.save("output/RosaceCircle.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Mosaique(image, 5);
    //     image.save("output/Mosaique.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Glitch(image);
    //     image.save("output/Glitch.png");
    // }

    // {
    //     sil::Image image{SpaceGradient()};
    //     image.save("output/SpaceGradient.png");

    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     MirrorMosaique(image, 5);
    //     image.save("output/MirrorMosaique.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     PixelSortTest(image);
    //     image.save("output/PixelSortTest.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     PixelSort(image);
    //     image.save("output/PixelSort.png");
    // }

    // {
        
    //     sil::Image image{SpaceGradientOklab()};
    //     image.save("output/SpaceGradientOklab.png");
    // }

    // {
    //     sil::Image image{MandelbrotFractal()};
    //     image.save("output/MandelbrotFractal.png");
    // }

    {
        sil::Image image{"images/logo.png"};
        VortexBug(image);
        image.save("output/VortexBug.png");

    }

    {
        sil::Image image{"images/logo.png"};
        VortexV1(image);
        image.save("output/VortexV1.png");

    }

    {
        sil::Image image{"images/logo.png"};
        Vortex(image);
        image.save("output/Vortex.png");

    }

    {
        sil::Image image{"images/photo_faible_contraste.jpg"};
        Normalisation(image);
        image.save("output/Normalisation.jpg");

    }


}