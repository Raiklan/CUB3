/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:09:09 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/04 19:09:12 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_player(t_info *info, t_img *tmp)
{
	/*int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 

	ra=FixAng(pa+30);                                                              //ray set back 30 degrees

	for(r=0;r<60;r++)
	{
	//---Vertical--- 
	dof=0; side=0; disV=100000;
	float Tan=tan(degToRad(ra));
	   if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
	else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
	else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

	while(dof<8) 
	{ 
	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	} 
	vx=rx; vy=ry;

	//---Horizontal---
	dof=0; disH=100000;
	Tan=1.0/Tan; 
	   if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
	else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
	else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right

	while(dof<8) 
	{ 
	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	} 

	glColor3f(0,0.8,0);
	if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
	glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray

	int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
	int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
	int lineOff = 160 - (lineH>>1);                                               //line offset

	ra=FixAng(ra-1);                                                              //go to next ray
	}*/


	int rayx;
	int rayy;
	float ray_dirx;
	float ray_diry;
	float next_full_x;
	float next_full_y;
	float le_restex;
	float le_restey;
	int stepx;
	int stepy;
	bool wall_hit;
	//bool side;

	t_coor	coor;

	info->color = 0x0000ff;
	coor.tile_size = info->tile_size;
	coor.xold = info->player.x;
	coor.yold = info->player.y;


	float rangle = info->player.angle;// - DEGREE * 30; //to be used with rayDir
	printf("rangle = %f | pangle = %f\n", rangle, info->player.angle);
	int rays = 0;
	while (rays < 1)
	{
		if (rangle < 0)
			rangle += 2 * PI;
		if (rangle > 2 * PI)
			rangle -= 2 * PI;
		printf("rangle = %f | pangle = %f\n", rangle, info->player.angle);
		rayx = info->player.x;
		rayy = info->player.y;

		/*else if (key_sym == 0xff51)//left
		{
			info->player.angle -= 0.1;
			if (info->player.angle < 0)
				info->player.angle += 2 * PI;
			info->player.dirx = cos(info->player.angle) * 5;
			info->player.diry = sin(info->player.angle) * 5;
		}
		else if (key_sym == 0xff53)//right
		{
			info->player.angle += 0.1;
			if (info->player.angle > 2 * PI) 
				info->player.angle -= 2 * PI;
			info->player.dirx = cos(info->player.angle) * 5;
			info->player.diry = sin(info->player.angle) * 5;
		}*/


		ray_dirx = cosf(rangle) * 5;//add camera/plane??
		ray_diry = sinf(rangle) * 5;
		printf("ray_dirx = %f, ray_diry = %f\n", ray_dirx ,ray_diry);
		wall_hit = 0;

		if (ray_dirx == 0)
			next_full_x = 1e30;
		else
			next_full_x = sqrtf(1 + (ray_diry * ray_diry) / (ray_dirx * ray_dirx));
		if (ray_diry == 0)
			next_full_y = 1e30;
		else
			next_full_y = sqrtf(1 + (ray_dirx * ray_dirx) / (ray_diry * ray_diry));
write(1, "here\n", 5);
		if (info->player.dirx < 0)
		{
			stepx = -1;
			le_restex = (info->player.x - rayx) * next_full_x;
		}
		else if (info->player.dirx > 0)
		{
			stepx = 1;
			le_restex = (rayx + 1.0 - info->player.x) * next_full_x;
		}
		if (info->player.diry < 0)
		{
			stepy = -1;
			le_restey = (info->player.y - rayy) * next_full_y;
		}
		else if (info->player.diry > 0)
		{
			stepy = 1;
			le_restey = (rayy + 1.0 - info->player.y) * next_full_y;
		}
write(1, "here\n", 5);
		while (wall_hit == 0)
		{
			if (le_restex < le_restey)
			{
				le_restex += next_full_x;
				rayx += stepx;
				//side = 0;//check angle too
			}
			else
			{
				le_restey += next_full_y;
				rayy += stepy;
				//side = 1;//check angle too
			}
			if (info->line[rayy/ info->tile_size][rayx/ info->tile_size] == '1')
				wall_hit = 1;
		}

		rays++;
		coor.x1 = rayx;
		coor.y1 = rayy;
		write(1, "here\n", 5);
		bresenham_new(info, tmp, &coor);
		rangle += DEGREE;
	}

	//t_coor coor;

	info->color = 0xff0000;
	coor.x1 = info->player.x + info->player.dirx * 5;
	coor.y1 = info->player.y + info->player.diry * 5;
	coor.xold = info->player.x;
	coor.yold = info->player.y;
	bresenham_new(info, tmp, &coor);
	info->color = 0xff0000;
	img_pix_put(info, tmp, info->player.x, info->player.y);
}

void	draw_minimap(t_info *info, t_img *tmp, int x, int y)
{
	int	i;
	int	j;
	int	pixel_count;
	int	col_count;

	i = 0;
	while (info->line[i])
    {
        col_count = 0;
        while (col_count < info->tile_size)
        {
            j = 0;
            while (info->line[i][j])
            {
                pixel_count = 0;
                while (pixel_count < info->tile_size)
                {
                    if (pixel_count == 0 || col_count == 0)
                        info->color = 0x0;
                    else if (pixel_count + 1 == info->tile_size || col_count + 1 == info->tile_size)
                    	info->color = 0xffffff;
                    else if (info->line[i][j] == '0')
                        info->color = 0xbdb76b;
                    else if (info->line[i][j] == '\t' || info->line[i][j] == ' ')
                        info->color = 0xcccccc;//{ "grey80" , 0xcccccc },
                    else
                        info->color = 0x696969;
                    img_pix_put(info, tmp, x, y);
                    pixel_count++;
                    x++;
                }
                j++;
            }
            y++;
            col_count++;
            x = 0;
        }
        i++;
    }
}

int    render(t_info *info)
{
    t_img    tmp;

    tmp.img_ptr = mlx_new_image(info->id, info->wd_width, info->wd_height);
    if (tmp.img_ptr == NULL)
        return (destroyer(info, info->line));
    tmp.addr = mlx_get_data_addr(tmp.img_ptr, &tmp.bpp, &tmp.line_len, &tmp.endian);
    info->color = 0x0;
    clear_background(info, &tmp);

    draw_minimap(info, &tmp, 0, 0);

    draw_player(info, &tmp);
    if (info->img.img_ptr != NULL)
    {
        mlx_destroy_image(info->id, info->img.img_ptr);
        info->img.img_ptr = NULL;
    }
    info->img.img_ptr = tmp.img_ptr;
    mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
    return (0);
}
