#include "Texture.hpp"
#include "../header/globalVar.hpp"
#include <SOIL/SOIL.h>
#include <cstdio>

modeler::Texture::Texture(const char* filename)
{

  /*-----------------------------------------------------------------------------
   *  Generate Texture and Bind it
   *-----------------------------------------------------------------------------*/
  glGenTextures(1, &TextureID);
  glBindTexture(GL_TEXTURE_2D, TextureID); 

  /*-----------------------------------------------------------------------------
   *  Allocate Memory on the GPU
   *-----------------------------------------------------------------------------*/
   
    int twidth, theight, nrComponents;
	unsigned char* image = SOIL_load_image(filename, &twidth, &theight, &nrComponents, SOIL_LOAD_AUTO);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		// target | lod | internal_format | width | height | border | format | type | data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D); // Generate MipMaps to use
		SOIL_free_image_data(image); // Free the data read from file after creating opengl texture 

	  /*-----------------------------------------------------------------------------
	   *  Set Texture Parameters
	   *-----------------------------------------------------------------------------*/
	   // Set these parameters to avoid a black screen caused by improperly mipmapped textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glActiveTexture(GL_TEXTURE0);
		/*-----------------------------------------------------------------------------
		 *  Unbind texture
		 *-----------------------------------------------------------------------------*/
		 // glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {

		printf("%s SOIL cannot load image \n%s\n", TAG_WARN.c_str(), filename);

	}
}
    
GLuint modeler::Texture::id() const { 
	return TextureID; 
}