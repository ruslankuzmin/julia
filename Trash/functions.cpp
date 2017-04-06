


///Ньютонова интерполяция - функция
bool polynomialfit(int obs, int degree, double *dx, double *dy, double *store) /* n, p */
{
  gsl_multifit_linear_workspace *ws;
  gsl_matrix *cov, *X;
  gsl_vector *y, *c;
  double chisq;
  int i, j;
  X = gsl_matrix_alloc(obs, degree);
  y = gsl_vector_alloc(obs);
  c = gsl_vector_alloc(degree);
  cov = gsl_matrix_alloc(degree, degree);
 
  for(i=0; i < obs; i++) {
    gsl_matrix_set(X, i, 0, 1.0);
    for(j=0; j < degree; j++) {
      gsl_matrix_set(X, i, j, pow(dx[i], j));
    }
    gsl_vector_set(y, i, dy[i]);
  }
 
  ws = gsl_multifit_linear_alloc(obs, degree);
  gsl_multifit_linear(X, y, c, cov, &chisq, ws);
 
  /* store result ... */
  for(i=0; i < degree; i++)
  {
    store[i] = gsl_vector_get(c, i);
  }
 
  gsl_multifit_linear_free(ws);
  gsl_matrix_free(X);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);
  return true; /* we do not "analyse" the result (cov matrix mainly)
		  to know if the fit is "good" */
}

///Перебор множеств подмножества
int pows()
{
    //множество
    int M[4] = {2, 5, 6, 9};
    //кол-во элементов множества
    int w = 4;
 
    int i, j, n;
    n = pow(2, w);
    //перебор битовых маск
    for ( i = 0; i < n; i++ )
    {
        printf("{");
	//перебор битов в маске
        for ( j = 0; j < w; j++ )
	    //если j-й бит установлен
            if ( i & (1 << j) )
 		//--то выводим j-й элемент множества
                printf("%d", M[j]);
        printf("}\n");
    }
    return 0;
}


///Создание html-кода для отображения фрагментов или сгенерированных картинок
std::string render_square(int array_pointer[10][10][3])
{
	int width=10;
	int height=10;
	string r,g,b;
	std::string output="";
	output+="<style>.render span{border-collapse:collapse;display:block;width:10px;height:10px;}</style>";
	output+="<div class='render'>";
	for(int x=0;x<width;++x)
	{
		for(int y=0;y<height;++y)
		{
		r = convert::to_string(array_pointer[x][y][0]);
		g = convert::to_string(array_pointer[x][y][1]);
		b = convert::to_string(array_pointer[x][y][2]);
		output+="<span style='line-height:6px;font-size:10px;color:rgb("+r+","+g+","+b+");background:rgb("+r+","+g+","+b+");'>***</span>";
		}
		output+="<br>";
	}
	output+="</div>";
return output;
}

std::string render_square_image(int** temp_patterns,int iter,std::string filename_pattern)
{
   const unsigned int dim = 10;

   bitmap_image image(dim,dim);

   for (unsigned int x = 0; x < dim; ++x)
   {
      for (unsigned int y = 0; y < dim; ++y)
      {
         //rgb_store col = jet_colormap[(x + y) % dim];
         image.set_pixel(x,y,(unsigned char)255,(unsigned char)255,(unsigned char)255);
      }
   }

    for (int i = 0; i < iter; ++i)
    {
 	// temp_patterns[i]
	
        image.set_pixel(
	(unsigned int)(9-temp_patterns[i][4]),
	(unsigned int)(9-temp_patterns[i][3]),
	(unsigned char)temp_patterns[i][0],
	(unsigned char)temp_patterns[i][1],
	(unsigned char)temp_patterns[i][2]
	);
	
    }

	std::string fn=convert::to_string(count_images);
        image.save_image("output/images/"+filename_pattern+fn+".bmp");
	count_images++;
	return fn;
}

std::string render_square_image2(int temp_patterns[10][10][3],std::string filename_pattern)
{
   const unsigned int dim = 10;
   bitmap_image image(dim,dim);
   for (unsigned int x = 0; x < dim; ++x)
   {
      for (unsigned int y = 0; y < dim; ++y)
      {
         image.set_pixel(x,y,
	(unsigned char)temp_patterns[x][y][0],
	(unsigned char)temp_patterns[x][y][1],
	(unsigned char)temp_patterns[x][y][2]
	);
      }
   }
	std::string fn=convert::to_string(count_images);
        image.save_image("output/images/"+filename_pattern+fn+".bmp");
	count_images++;
	return fn;
}

///Загрузка bmp-изображения в массив
int loadBMP(std::string file_name)
{
 unsigned char red;
 unsigned char green;
 unsigned char blue;
  	 bitmap_image image(file_name);
  	 if (!image)
  	 {
        	printf("Error - Failed to open '%s'\n",file_name.c_str());
  	 }	
		int dim=10;
		  for (unsigned int x = 0; x < dim; ++x)
		   {
		      for (unsigned int y = 0; y < dim; ++y)
		      {
			 image.get_pixel(y,x,red,green,blue);
			 pixels_image[x][y][0]=(unsigned int)red;
			 pixels_image[x][y][1]=(unsigned int)green;
			 pixels_image[x][y][2]=(unsigned int)blue;
		      }
		   }
	return 0;
}



//Разделение строки на подстроки

map <int,string> split(std::string delimiter,std::string s)
{
size_t pos = 0;
std::string token;
map <int,string> tokens;
int i=0;
while ((pos = s.find(delimiter)) != std::string::npos) {
    //std::cout << token << std::endl;
    tokens[i]= s.substr(0, pos);
    i++;
    s.erase(0, pos + delimiter.length());
}
return tokens;
}

