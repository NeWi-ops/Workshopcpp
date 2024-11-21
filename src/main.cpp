#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include "random.hpp"
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>




void KeepGreenOnly (sil::Image& image)
{
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
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3 (color.b, color.g, color.r);
    }

}


void BlackAndWhiteBug (sil::Image& image) 
{
    for (glm::vec3& color : image.pixels())
    {
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    gray = (gray > 0.5f) ? 1.0f : 0.0f;
    color = glm::vec3{gray};
    }
}

void BlackAndWhite (sil::Image& image) 
{
    for (glm::vec3& color : image.pixels())
    {
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    color = glm::vec3{gray};
    }
}

void Negative (sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3 (1-color.b, 1-color.g, 1-color.r);
    }
}

sil::Image Gradient ()
{
    sil::Image image{300, 200};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }    
    return image;
}

void MirrorBug (sil::Image& image)
{
    for (int x{0}; x < (image.width())/2; x++)
    {
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x,y)=image.pixel(image.width()-1-x,image.height()-1-y);
    }
}
}

void MirrorBug2 (sil::Image& image)
{
    for (int x{0}; x < (image.width()); x++)
    {
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x,y)=image.pixel(image.width()-1-x,y);
    }
    }
}

void Mirror (sil::Image& image)
{
    for (int x{0}; x < (image.width()/2); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y),image.pixel((image.width())-1-x,y));
        }
    }
}

void Noise (sil::Image& image)
{
    int width {image.width()};
    int height {image.height()};

    for (int i{}; i<50000; i++)
    {
        int x = std::rand() % width;   
        int y = std::rand() % height;

        float r = static_cast<float>(std::rand()) / RAND_MAX;
        float g = static_cast<float>(std::rand()) / RAND_MAX;
        float b = static_cast<float>(std::rand()) / RAND_MAX;

        image.pixel(x,y).r = r;
        image.pixel(x,y).g = g;
        image.pixel(x,y).b = b;
    }
}

void Rotation (sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    sil::Image rotatedImage(height, width);

    for (int x = 0; x < width; x++) 
    {
        for (int y = 0; y < height; y++) 
        {
            rotatedImage.pixel(height - 1 - y, x)=image.pixel(x,y);
        }
    }
    image = rotatedImage;
}

void RGBsplit (sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    sil::Image splitimage(width, height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (x>30)
            {
                splitimage.pixel(x,y).b=image.pixel(x-30,y).b;
            }
            else
            {
                splitimage.pixel(x,y).b=image.pixel(x,y).b;
            }

            if (x<width-30)
            {
                splitimage.pixel(x,y).r=image.pixel(x+30,y).r;
            }
            else
            {
                splitimage.pixel(x,y).r=image.pixel(x,y).r;
            }

            splitimage.pixel(x,y).g=image.pixel(x,y).g;
        
        }
    }
    image = splitimage;
}

void Brightness (sil::Image& image, float p)
{
    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            

            
            image.pixel(x,y).r = std::pow(image.pixel(x,y).r, p);   
            image.pixel(x,y).g = std::pow(image.pixel(x,y).g, p);   
            image.pixel(x,y).b = std::pow(image.pixel(x,y).b, p);   

            
            
        }
    }
}

sil::Image Disk ()
{
    sil::Image image{500, 500};

    int width = image.width();
    int height = image.height();
    int centerX {250};
    int centerY {250};
    int radius {10000};
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            int dx {x - centerX};
            int dy {y - centerY};
            int distanceSquared {dx * dx + dy * dy};

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
    
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            int dx = x - centerX;
            int dy = y - centerY;
            int distance = static_cast<int>(std::sqrt(dx * dx + dy * dy));

            
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
    
    sil::Image image{500, 500};
    int width = image.width();
    int height = image.height();
    int centerX {};
    int centerY {250};
    int radius {10000};
    for (int i {0}; i<30; i++)
    {
        sil::Image image{500, 500};
        for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x) 
            {
                int dx {x - centerX};
                int dy {y - centerY};
                int distanceSquared {dx * dx + dy * dy};

                if (distanceSquared<radius)
                {
                    image.pixel(x,y)=glm::vec3{1, 1, 1};
                }
            }
            
        }
        centerX += width/30;
        image.save("output/animation/diskframe"+std::to_string(i)+".png");
    }    
    
    return image;
}

sil::Image RosaceBug()
{
    sil::Image image{500, 500};
    int height {image.height()};
    int width {image.width()};
    int radius {100};
    int centerX {250};
    int centerY {250};
    int thickness{5};
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
                int distanceSquared {dx * dx + dy * dy};

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
    
    Circle(image, centerX, centerY, radius, thickness);
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
    sil::Image Mosa{image.width(), image.height()};
    for (int y = 0; y < image.height(); ++y) 
        {
            for (int x = 0; x < image.width(); ++x) 
            {
                int x2 {x%(image.width()/nombre)};
                int y2 {y%(image.height()/nombre)};
                Mosa.pixel(x,y)=image.pixel(x2*nombre,y2*nombre);
            }
        }
        image = Mosa;

}

void MirrorMosaique(sil::Image& image, int nombre)
{
    sil::Image Mosa(image.width(), image.height());

    int width = image.width() / nombre;
    int height = image.height() / nombre;

    for (int y = 0; y < image.height(); ++y) 
    {
        for (int x = 0; x < image.width(); ++x) 
        {
            // Calcul des coordonnées de la tuile
            int x2 = x % width;
            int y2 = y % height;

            // Inverser les coordonnées des x si la ligne est impaire
            if ((x / width)%2==1) 
            {  // Ligne impaire et colonne paire
                x2 = width - 1 - x2;  
                   // Inversion
            }

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
    // Initialisation du générateur de nombres aléatoires
    

    // Dimensions de l'image
    int width = image.width();
    int height = image.height();

    
    for (int i{}; i<50; i++)
    {

    
        //taille de rectangle aléatoire
        int rectWidth = random_int(20, 40);
        int rectHeight = random_int(2, 10);
        
        

        // S'assurer que les rectangles ne dépassent pas les bords de l'image
        int maxX = width - rectWidth;
        int maxY = height - rectHeight;

    


        // Choisir des positions aléatoires pour les rectangles
        int x1 = std::rand() % maxX;
        int y1 = std::rand() % maxY;
        int x2 = std::rand() % maxX;
        int y2 = std::rand() % maxY;

        // Copier les pixels du premier rectangle 
        sil::Image rect1(rectWidth, rectHeight);
        for (int i = 0; i < rectHeight; ++i) {
            for (int j = 0; j < rectWidth; ++j) {
                rect1.pixel(j, i) = image.pixel(x1 + j, y1 + i);
            }
        }

        // Copier les pixels du second rectangle dans un buffer temporaire
        sil::Image rect2(rectWidth, rectHeight);
        for (int i = 0; i < rectHeight; ++i) {
            for (int j = 0; j < rectWidth; ++j) {
                rect2.pixel(j, i) = image.pixel(x2 + j, y2 + i);
            }
        }

        // Échanger les pixels des rectangles
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
     

    std::sort(image.pixels().begin(), image.pixels().end(), [](const glm::vec3& color1, const glm::vec3& color2) {
        return glm::length(color1) < glm::length(color2);
    });
}

void PixelSort(sil::Image& image)
{
    int width = image.width();
    int height = image.height();
   
    // {
       
    //    for (int y{0}; y<height; y++)
    //    {
    //         int espacement = random_int(50,200);
    //         for (int x{espacement}; x<width; x = x + espacement)
    //         {
    //             int longueur = random_int(60,150);
    //             espacement = random_int(10,50);
    //             std::sort(image.pixels().begin()+x+espacement, image.pixels().begin()+x+espacement+longueur, [](const glm::vec3& color1, const glm::vec3& color2)
    //             {
    //                 return glm::length(color1) < glm::length(color2);
    //             });
    //         }
    //    }
    // }
    for (int y = 0; y < height; ++y) 
    { 
        int x = 0; 
        while (x < width) 
        {
            int espacement = random_int(0, 100); 
            x += espacement;
            if (x >= width) break;

            int longueur = random_int(30, 50);
            int end = std::min(x + longueur, width);

            
            std::sort(image.pixels().begin() + y * width + x, image.pixels().begin() + y * width + end,    
                [](const glm::vec3& color1, const glm::vec3& color2) 
                {
                    return glm::length(color1) < glm::length(color2);
                });

            x = end;
        }
    }
}

sil::Image SpaceGradient()
{
    sil::Image image{500,500};
    glm::vec3 color1(1.0f, 0.0f, 0.0f);  // Rouge
    glm::vec3 color2(0.0f, 0.0f, 1.0f);  // Bleu

    // Dimensions de l'image
    int width = image.width();
    int height = image.height();

    // Appliquer le dégradé sur chaque pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculer le facteur de mélange en fonction de la position du pixel (par exemple sur l'axe X)
            float mixFactor = static_cast<float>(x) / width;

            // Mélanger les deux couleurs en fonction du facteur de mélange
            glm::vec3 mixedColor = (glm::mix((color1), (color2), mixFactor));


            // Assigner la couleur au pixel de l'image
            image.pixel(x, y) = mixedColor;
        }
    }
    return image;
}

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
    sil::Image image{500, 500};
    glm::vec3 color1(1.0f, 0.0f, 0.0f);  
    glm::vec3 color2(0.0f, 0.0f, 1.0f);  

    int width = image.width();
    int height = image.height();

    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            float mixFactor = static_cast<float>(x) / width;

            
            glm::vec3 mixedColor = rgb(glm::mix(lab(color1), lab(color2), mixFactor));

            image.pixel(x, y) = mixedColor;
        }
    }
    
    return image;
    
}

sil::Image MandelbrotFractal()
{
   
    sil::Image image{2000,2000};
    int width = image.width();
    int height = image.height();
    int MaxIteration {1000};
    for (int x = 0; x<width; x++)
    {
        for (int y = 0; y<height; y++)
        {
            double a {(static_cast<double>(x)/width)*4.0-2.0};
            double b {(static_cast<double>(y)/width)*4.0-2.0};
            std::complex<double> c(a, b);
            std::complex<double> z(0, 0);

            int iteration{0};
            while(iteration<MaxIteration && std::abs(z)<=2.0)
            {
                z = z * z + c;
                iteration+=1;
            }
            if (iteration==MaxIteration)
            {
                image.pixel(x,y) = glm::vec3(1.0f,0.0f,0.0f);

            }
            else 
            {
                
                float gray = static_cast<float>(iteration) / (30);
                image.pixel(x, y) = glm::vec3(gray, 0.0f, 0.0f); 
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

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void VortexBug(sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    double maxangle = M_PI;
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
        }
    }


}

void VortexV1(sil::Image& image)
{
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
                glm::vec3 black(0.0f, 0.0f, 0.0f);
                image.pixel(x,y) = black;
            }
        }
    }
}

void Vortex(sil::Image& image)
{
    sil::Image Vortex{image.width(),image.height()};
    int Vwidth = Vortex.width();
    int Vheight = Vortex.height();
    int Iwidth = image.width();
    int Iheight = image.height();
    double maxangle = 10*M_PI;
    glm::vec2 CenterRotation(Iwidth/2, Iheight/2);

    for (int y = 0; y < Iheight; ++y) 
    {
        for (int x = 0; x < Iwidth; ++x) 
        {
            glm::vec2 point(x, y);
            float distance = glm::distance(point, CenterRotation);
            float angle = maxangle * (distance / std::max(Iwidth, Iheight));
            glm::vec2 rotatedPoint = rotated(point, CenterRotation, angle);

            if (rotatedPoint.x >= 0 && rotatedPoint.x < Vwidth && rotatedPoint.y >= 0 && rotatedPoint.y < Vheight) 
            {
                Vortex.pixel(x, y) = image.pixel(static_cast<int>(rotatedPoint.x), static_cast<int>(rotatedPoint.y));
            }
            // else
            // {
            //     glm::vec3 black(0.0f, 0.0f, 0.0f);
            //     image.pixel(x,y) = black;
            // }
        }
    }
    image = Vortex;

}

void Normalisation(sil::Image image)
{
    int width {image.width()};
    int height {image.height()};
    sil::Image normalisation{width,height};

    float minLumi{1.0f}
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

    // {
    //     sil::Image image{"images/logo.png"};
    //     VortexBug(image);
    //     image.save("output/VortexBug.png");

    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     VortexV1(image);
    //     image.save("output/VortexV1.png");

    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Vortex(image);
    //     image.save("output/VortexV1.png");

    // }


}