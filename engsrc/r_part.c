/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "quakedef.h"


#define MAX_PARTICLES			2048	// default max # of particles at one
										//  time
#define ABSOLUTE_MIN_PARTICLES	512		// no fewer than this no matter what's
										//  on the command line

int		ramp1[8] = {0x6f, 0x6d, 0x6b, 0x69, 0x67, 0x65, 0x63, 0x61};
int		ramp2[8] = {0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x68, 0x66};
int		ramp3[8] = {0x6d, 0x6b, 6, 5, 4, 3};

particle_t	*active_particles, *free_particles;

particle_t	*particles;
int			r_numparticles;

vec3_t			r_pright, r_pup, r_ppn;
//move this to a header
GLfloat PaletteTable[256][3] = {
{0, 0, 0},
{15, 15, 15},
{31, 31, 31},
{47, 47, 47},
{63, 63, 63},
{75, 75, 75},
{91, 91, 91},
{107, 107, 107},
{123, 123, 123},
{139, 139, 139},
{155, 155, 155},
{171, 171, 171},
{187, 187, 187},
{203, 203, 203},
{219, 219, 219},
{235, 235, 235},
{15, 11, 7},
{23, 15, 11},
{31, 23, 11},
{39, 27, 15},
{47, 35, 19},
{55, 43, 23},
{63, 47, 23},
{75, 55, 27},
{83, 59, 27},
{91, 67, 31},
{99, 75, 31},
{107, 83, 31},
{115, 87, 31},
{123, 95, 35},
{131, 103, 35},
{143, 111, 35},
{11, 11, 15},
{19, 19, 27},
{27, 27, 39},
{39, 39, 51},
{47, 47, 63},
{55, 55, 75},
{63, 63, 87},
{71, 71, 103},
{79, 79, 115},
{91, 91, 127},
{99, 99, 139},
{107, 107, 151},
{115, 115, 163},
{123, 123, 175},
{131, 131, 187},
{139, 139, 203},
{0, 0, 0},
{7, 7, 0},
{11, 11, 0},
{19, 19, 0},
{27, 27, 0},
{35, 35, 0},
{43, 43, 7},
{47, 47, 7},
{55, 55, 7},
{63, 63, 7},
{71, 71, 7},
{75, 75, 11},
{83, 83, 11},
{91, 91, 11},
{99, 99, 11},
{107, 107, 15},
{7, 0, 0},
{15, 0, 0},
{23, 0, 0},
{31, 0, 0},
{39, 0, 0},
{47, 0, 0},
{55, 0, 0},
{63, 0, 0},
{71, 0, 0},
{79, 0, 0},
{87, 0, 0},
{95, 0, 0},
{103, 0, 0},
{111, 0, 0},
{119, 0, 0},
{127, 0, 0},
{19, 19, 0},
{27, 27, 0},
{35, 35, 0},
{47, 43, 0},
{55, 47, 0},
{67, 55, 0},
{75, 59, 7},
{87, 67, 7},
{95, 71, 7},
{107, 75, 11},
{119, 83, 15},
{131, 87, 19},
{139, 91, 19},
{151, 95, 27},
{163, 99, 31},
{175, 103, 35},
{35, 19, 7},
{47, 23, 11},
{59, 31, 15},
{75, 35, 19},
{87, 43, 23},
{99, 47, 31},
{115, 55, 35},
{127, 59, 43},
{143, 67, 51},
{159, 79, 51},
{175, 99, 47},
{191, 119, 47},
{207, 143, 43},
{223, 171, 39},
{239, 203, 31},
{255, 243, 27},
{11, 7, 0},
{27, 19, 0},
{43, 35, 15},
{55, 43, 19},
{71, 51, 27},
{83, 55, 35},
{99, 63, 43},
{111, 71, 51},
{127, 83, 63},
{139, 95, 71},
{155, 107, 83},
{167, 123, 95},
{183, 135, 107},
{195, 147, 123},
{211, 163, 139},
{227, 179, 151},
{171, 139, 163},
{159, 127, 151},
{147, 115, 135},
{139, 103, 123},
{127, 91, 111},
{119, 83, 99},
{107, 75, 87},
{95, 63, 75},
{87, 55, 67},
{75, 47, 55},
{67, 39, 47},
{55, 31, 35},
{43, 23, 27},
{35, 19, 19},
{23, 11, 11},
{15, 7, 7},
{187, 115, 159},
{175, 107, 143},
{163, 95, 131},
{151, 87, 119},
{139, 79, 107},
{127, 75, 95},
{115, 67, 83},
{107, 59, 75},
{95, 51, 63},
{83, 43, 55},
{71, 35, 43},
{59, 31, 35},
{47, 23, 27},
{35, 19, 19},
{23, 11, 11},
{15, 7, 7},
{219, 195, 187},
{203, 179, 167},
{191, 163, 155},
{175, 151, 139},
{163, 135, 123},
{151, 123, 111},
{135, 111, 95},
{123, 99, 83},
{107, 87, 71},
{95, 75, 59},
{83, 63, 51},
{67, 51, 39},
{55, 43, 31},
{39, 31, 23},
{27, 19, 15},
{15, 11, 7},
{111, 131, 123},
{103, 123, 111},
{95, 115, 103},
{87, 107, 95},
{79, 99, 87},
{71, 91, 79},
{63, 83, 71},
{55, 75, 63},
{47, 67, 55},
{43, 59, 47},
{35, 51, 39},
{31, 43, 31},
{23, 35, 23},
{15, 27, 19},
{11, 19, 11},
{7, 11, 7},
{255, 243, 27},
{239, 223, 23},
{219, 203, 19},
{203, 183, 15},
{187, 167, 15},
{171, 151, 11},
{155, 131, 7},
{139, 115, 7},
{123, 99, 7},
{107, 83, 0},
{91, 71, 0},
{75, 55, 0},
{59, 43, 0},
{43, 31, 0},
{27, 15, 0},
{11, 7, 0},
{0, 0, 255},
{11, 11, 239},
{19, 19, 223},
{27, 27, 207},
{35, 35, 191},
{43, 43, 175},
{47, 47, 159},
{47, 47, 143},
{47, 47, 127},
{47, 47, 111},
{47, 47, 95},
{43, 43, 79},
{35, 35, 63},
{27, 27, 47},
{19, 19, 31},
{11, 11, 15},
{43, 0, 0},
{59, 0, 0},
{75, 7, 0},
{95, 7, 0},
{111, 15, 0},
{127, 23, 7},
{147, 31, 7},
{163, 39, 11},
{183, 51, 15},
{195, 75, 27},
{207, 99, 43},
{219, 127, 59},
{227, 151, 79},
{231, 171, 95},
{239, 191, 119},
{247, 211, 139},
{167, 123, 59},
{183, 155, 55},
{199, 195, 55},
{231, 227, 87},
{127, 191, 255},
{171, 231, 255},
{215, 255, 255},
{103, 0, 0},
{139, 0, 0},
{179, 0, 0},
{215, 0, 0},
{255, 0, 0},
{255, 243, 147},
{255, 247, 199},
{255, 255, 255},
{159, 91, 83}
};




/*
===============
R_InitParticles
===============
*/
void R_InitParticles (void)
{
	int		i;

	i = COM_CheckParm ("-particles");

	if (i)
	{
		r_numparticles = (int)(Q_atoi(com_argv[i+1]));
		if (r_numparticles < ABSOLUTE_MIN_PARTICLES)
			r_numparticles = ABSOLUTE_MIN_PARTICLES;
	}
	else
	{
		r_numparticles = MAX_PARTICLES;
	}

	particles = (particle_t *)
			Hunk_AllocName (r_numparticles * sizeof(particle_t), "particles");
}

#ifdef QUAKE2
void R_DarkFieldParticles (entity_t *ent)
{
	int			i, j, k;
	particle_t	*p;
	float		vel;
	vec3_t		dir;
	vec3_t		org;

	org[0] = ent->origin[0];
	org[1] = ent->origin[1];
	org[2] = ent->origin[2];
	for (i=-16 ; i<16 ; i+=8)
		for (j=-16 ; j<16 ; j+=8)
			for (k=0 ; k<32 ; k+=8)
			{
				if (!free_particles)
					return;
				p = free_particles;
				free_particles = p->next;
				p->next = active_particles;
				active_particles = p;
		
				p->die = cl.time + 0.2 + (rand()&7) * 0.02;
				p->color = 150 + rand()%6;
				p->type = pt_slowgrav;
				
				dir[0] = j*8;
				dir[1] = i*8;
				dir[2] = k*8;
	
				p->org[0] = org[0] + i + (rand()&3);
				p->org[1] = org[1] + j + (rand()&3);
				p->org[2] = org[2] + k + (rand()&3);
	
				VectorNormalize (dir);						
				vel = 50 + (rand()&63);
				VectorScale (dir, vel, p->vel);
			}
}
#endif


/*
===============
R_EntityParticles
===============
*/

#define NUMVERTEXNORMALS	162
extern	float	r_avertexnormals[NUMVERTEXNORMALS][3];
vec3_t	avelocities[NUMVERTEXNORMALS];
float	beamlength = 16;
vec3_t	avelocity = {23, 7, 3};
float	partstep = 0.01;
float	timescale = 0.01;

void R_EntityParticles (entity_t *ent)
{
	int			count;
	int			i;
	particle_t	*p;
	float		angle;
	float		sr, sp, sy, cr, cp, cy;
	vec3_t		forward;
	float		dist;
	
	dist = 64;
	count = 50;

if (!avelocities[0][0])
{
for (i=0 ; i<NUMVERTEXNORMALS*3 ; i++)
avelocities[0][i] = (rand()&255) * 0.01;
}


	for (i=0 ; i<NUMVERTEXNORMALS ; i++)
	{
		angle = cl.time * avelocities[i][0];
		sy = sin(angle);
		cy = cos(angle);
		angle = cl.time * avelocities[i][1];
		sp = sin(angle);
		cp = cos(angle);
		angle = cl.time * avelocities[i][2];
		sr = sin(angle);
		cr = cos(angle);
	
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;

		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;

		p->die = cl.time + 0.01;
		p->color = 0x6f;
		p->type = pt_explode;
		
		p->org[0] = ent->origin[0] + r_avertexnormals[i][0]*dist + forward[0]*beamlength;			
		p->org[1] = ent->origin[1] + r_avertexnormals[i][1]*dist + forward[1]*beamlength;			
		p->org[2] = ent->origin[2] + r_avertexnormals[i][2]*dist + forward[2]*beamlength;			
	}
}


/*
===============
R_ClearParticles
===============
*/
void R_ClearParticles (void)
{
	int		i;
	
	free_particles = &particles[0];
	active_particles = NULL;

	for (i=0 ;i<r_numparticles ; i++)
		particles[i].next = &particles[i+1];
	particles[r_numparticles-1].next = NULL;
}


void R_ReadPointFile_f (void)
{
	FILE	*f;
	vec3_t	org;
	int		r;
	int		c;
	particle_t	*p;
	char	name[MAX_OSPATH];
	
	sprintf (name,"maps/%s.pts", sv.name);

	COM_FOpenFile (name, &f);
	if (!f)
	{
		Con_Printf ("couldn't open %s\n", name);
		return;
	}
	
	Con_Printf ("Reading %s...\n", name);
	c = 0;
	for ( ;; )
	{
		r = fscanf (f,"%f %f %f\n", &org[0], &org[1], &org[2]);
		if (r != 3)
			break;
		c++;
		
		if (!free_particles)
		{
			Con_Printf ("Not enough free particles\n");
			break;
		}
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;
		
		p->die = 99999;
		p->color = (-c)&15;
		p->type = pt_static;
		VectorCopy (vec3_origin, p->vel);
		VectorCopy (org, p->org);
	}

	fclose (f);
	Con_Printf ("%i points read\n", c);
}

/*
===============
R_ParseParticleEffect

Parse an effect out of the server message
===============
*/
void R_ParseParticleEffect (void)
{
	vec3_t		org, dir;
	int			i, count, msgcount, color;
	
	for (i=0 ; i<3 ; i++)
		org[i] = MSG_ReadCoord ();
	for (i=0 ; i<3 ; i++)
		dir[i] = MSG_ReadChar () * (1.0/16);
	msgcount = MSG_ReadByte ();
	color = MSG_ReadByte ();

if (msgcount == 255)
	count = 1024;
else
	count = msgcount;
	
	R_RunParticleEffect (org, dir, color, count);
}
	
/*
===============
R_ParticleExplosion

===============
*/
void R_ParticleExplosion (vec3_t org)
{
	int			i, j;
	particle_t	*p;
	
	for (i=0 ; i<1024 ; i++)
	{
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;

		p->die = cl.time + 5;
		p->color = ramp1[0];
		p->ramp = rand()&3;
		if (i & 1)
		{
			p->type = pt_explode;
			for (j=0 ; j<3 ; j++)
			{
				p->org[j] = org[j] + ((rand()%32)-16);
				p->vel[j] = (rand()%512)-256;
			}
		}
		else
		{
			p->type = pt_explode2;
			for (j=0 ; j<3 ; j++)
			{
				p->org[j] = org[j] + ((rand()%32)-16);
				p->vel[j] = (rand()%512)-256;
			}
		}
	}
}

/*
===============
R_ParticleExplosion2

===============
*/
void R_ParticleExplosion2 (vec3_t org, int colorStart, int colorLength)
{
	int			i, j;
	particle_t	*p;
	int			colorMod = 0;

	for (i=0; i<512; i++)
	{
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;

		p->die = cl.time + 0.3;
		p->color = colorStart + (colorMod % colorLength);
		colorMod++;

		p->type = pt_blob;
		for (j=0 ; j<3 ; j++)
		{
			p->org[j] = org[j] + ((rand()%32)-16);
			p->vel[j] = (rand()%512)-256;
		}
	}
}

/*
===============
R_BlobExplosion

===============
*/
void R_BlobExplosion (vec3_t org)
{
	int			i, j;
	particle_t	*p;
	
	for (i=0 ; i<1024 ; i++)
	{
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;

		p->die = cl.time + 1 + (rand()&8)*0.05;

		if (i & 1)
		{
			p->type = pt_blob;
			p->color = 66 + rand()%6;
			for (j=0 ; j<3 ; j++)
			{
				p->org[j] = org[j] + ((rand()%32)-16);
				p->vel[j] = (rand()%512)-256;
			}
		}
		else
		{
			p->type = pt_blob2;
			p->color = 150 + rand()%6;
			for (j=0 ; j<3 ; j++)
			{
				p->org[j] = org[j] + ((rand()%32)-16);
				p->vel[j] = (rand()%512)-256;
			}
		}
	}
}

/*
===============
R_RunParticleEffect

===============
*/
void R_RunParticleEffect (vec3_t org, vec3_t dir, int color, int count)
{
	int			i, j;
	particle_t	*p;
	
	for (i=0 ; i<count ; i++)
	{
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;

		if (count == 1024)
		{	// rocket explosion
			p->die = cl.time + 5;
			p->color = ramp1[0];
			p->ramp = rand()&3;
			if (i & 1)
			{
				p->type = pt_explode;
				for (j=0 ; j<3 ; j++)
				{
					p->org[j] = org[j] + ((rand()%32)-16);
					p->vel[j] = (rand()%512)-256;
				}
			}
			else
			{
				p->type = pt_explode2;
				for (j=0 ; j<3 ; j++)
				{
					p->org[j] = org[j] + ((rand()%32)-16);
					p->vel[j] = (rand()%512)-256;
				}
			}
		}
		else
		{
			p->die = cl.time + 0.1*(rand()%5);
			p->color = (color&~7) + (rand()&7);
			p->type = pt_slowgrav;
			for (j=0 ; j<3 ; j++)
			{
				p->org[j] = org[j] + ((rand()&15)-8);
				p->vel[j] = dir[j]*15;// + (rand()%300)-150;
			}
		}
	}
}


/*
===============
R_LavaSplash

===============
*/
void R_LavaSplash (vec3_t org)
{
	int			i, j, k;
	particle_t	*p;
	float		vel;
	vec3_t		dir;

	for (i=-16 ; i<16 ; i++)
		for (j=-16 ; j<16 ; j++)
			for (k=0 ; k<1 ; k++)
			{
				if (!free_particles)
					return;
				p = free_particles;
				free_particles = p->next;
				p->next = active_particles;
				active_particles = p;
		
				p->die = cl.time + 2 + (rand()&31) * 0.02;
				p->color = 224 + (rand()&7);
				p->type = pt_slowgrav;
				
				dir[0] = j*8 + (rand()&7);
				dir[1] = i*8 + (rand()&7);
				dir[2] = 256;
	
				p->org[0] = org[0] + dir[0];
				p->org[1] = org[1] + dir[1];
				p->org[2] = org[2] + (rand()&63);
	
				VectorNormalize (dir);						
				vel = 50 + (rand()&63);
				VectorScale (dir, vel, p->vel);
			}
}

/*
===============
R_TeleportSplash

===============
*/
void R_TeleportSplash (vec3_t org)
{
	int			i, j, k;
	particle_t	*p;
	float		vel;
	vec3_t		dir;

	for (i=-16 ; i<16 ; i+=4)
		for (j=-16 ; j<16 ; j+=4)
			for (k=-24 ; k<32 ; k+=4)
			{
				if (!free_particles)
					return;
				p = free_particles;
				free_particles = p->next;
				p->next = active_particles;
				active_particles = p;
		
				p->die = cl.time + 0.2 + (rand()&7) * 0.02;
				p->color = 7 + (rand()&7);
				p->type = pt_slowgrav;
				
				dir[0] = j*8;
				dir[1] = i*8;
				dir[2] = k*8;
	
				p->org[0] = org[0] + i + (rand()&3);
				p->org[1] = org[1] + j + (rand()&3);
				p->org[2] = org[2] + k + (rand()&3);
	
				VectorNormalize (dir);						
				vel = 50 + (rand()&63);
				VectorScale (dir, vel, p->vel);
			}
}

void R_RocketTrail (vec3_t start, vec3_t end, int type)
{
	vec3_t		vec;
	float		len;
	int			j;
	particle_t	*p;
	int			dec;
	static int	tracercount;

	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);
	if (type < 128)
		dec = 3;
	else
	{
		dec = 1;
		type -= 128;
	}

	while (len > 0)
	{
		len -= dec;

		if (!free_particles)
			return;
		p = free_particles;
		free_particles = p->next;
		p->next = active_particles;
		active_particles = p;
		
		VectorCopy (vec3_origin, p->vel);
		p->die = cl.time + 2;

		switch (type)
		{
			case 0:	// rocket trail
				p->ramp = (rand()&3);
				p->color = ramp3[(int)p->ramp];
				p->type = pt_fire;
				for (j=0 ; j<3 ; j++)
					p->org[j] = start[j] + ((rand()%6)-3);
				break;

			case 1:	// smoke smoke
				p->ramp = (rand()&3) + 2;
				p->color = ramp3[(int)p->ramp];
				p->type = pt_fire;
				for (j=0 ; j<3 ; j++)
					p->org[j] = start[j] + ((rand()%6)-3);
				break;

			case 2:	// blood
				p->type = pt_grav;
				p->color = 67 + (rand()&3);
				for (j=0 ; j<3 ; j++)
					p->org[j] = start[j] + ((rand()%6)-3);
				break;

			case 3:
			case 5:	// tracer
				p->die = cl.time + 0.5;
				p->type = pt_static;
				if (type == 3)
					p->color = 52 + ((tracercount&4)<<1);
				else
					p->color = 230 + ((tracercount&4)<<1);
			
				tracercount++;

				VectorCopy (start, p->org);
				if (tracercount & 1)
				{
					p->vel[0] = 30*vec[1];
					p->vel[1] = 30*-vec[0];
				}
				else
				{
					p->vel[0] = 30*-vec[1];
					p->vel[1] = 30*vec[0];
				}
				break;

			case 4:	// slight blood
				p->type = pt_grav;
				p->color = 67 + (rand()&3);
				for (j=0 ; j<3 ; j++)
					p->org[j] = start[j] + ((rand()%6)-3);
				len -= 3;
				break;

			case 6:	// voor trail
				p->color = 9*16 + 8 + (rand()&3);
				p->type = pt_static;
				p->die = cl.time + 0.3;
				for (j=0 ; j<3 ; j++)
					p->org[j] = start[j] + ((rand()&15)-8);
				break;
		}
		

		VectorAdd (start, vec, start);
	}
}


/*
===============
R_DrawParticles
===============
*/
extern	cvar_t	sv_gravity;

void R_DrawParticles (void)
{
	particle_t		*p, *kill;
	float			grav;
	int				i;
	float			time2, time3;
	float			time1;
	float			dvel;
	float			frametime;
	

	vec3_t			up, right;
	float			scale;
	

	unsigned	*rgba;
	int   pcol;


    GL_Bind(particletexture);
	glEnable (GL_BLEND);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glBegin (GL_TRIANGLES);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	VectorScale (vup, 1.5, up);
	VectorScale (vright, 1.5, right);

	frametime = cl.time - cl.oldtime;
	time3 = frametime * 15;
	time2 = frametime * 10; // 15;
	time1 = frametime * 5;
	grav = frametime * sv_gravity.value * 0.05;
	dvel = 4*frametime;
	
	for ( ;; ) 
	{
		kill = active_particles;
		if (kill && kill->die < cl.time)
		{
			active_particles = kill->next;
			kill->next = free_particles;
			free_particles = kill;
			continue;
		}
		break;
	}

	for (p=active_particles ; p ; p=p->next)
	{
		for ( ;; )
		{
			kill = p->next;
			if (kill && kill->die < cl.time)
			{
				p->next = kill->next;
				kill->next = free_particles;
				free_particles = kill;
				continue;
			}
			break;
		}


		// hack a scale up to keep particles from disapearing
		scale = (p->org[0] - r_origin[0])*vpn[0] + (p->org[1] - r_origin[1])*vpn[1]
			+ (p->org[2] - r_origin[2])*vpn[2];
		if (scale < 20)
			scale = 1;
		else
			scale = 1 + scale * 0.004;
		//glColor3ubv ((byte *)&d_8to24table[(int)p->color]);
		//glTexCoord2f (0,0);
		//glVertex3fv (p->org);
		//glTexCoord2f (1,0);
		//glVertex3f (p->org[0] + up[0]*scale, p->org[1] + up[1]*scale, p->org[2] + up[2]*scale);
		//glTexCoord2f (0,1);
		//glVertex3f (p->org[0] + right[0]*scale, p->org[1] + right[1]*scale, p->org[2] + right[2]*scale);
		pcol = (int)p->color-1;
		float acol = 1.0;
		if(pcol == 255) acol = 0.1;
		//rgba = &d_8to24table[(int)p->color];
		//Sys_Printf("part color R:%0.2f, G:%0.2f, B:%0.2f/n",rgba[0],rgba[1],rgba[2]);
		//glColor4f(rgba[0],rgba[1],rgba[2],1);
		//glColor4f(255,0,0,1);
		glColor4f(PaletteTable[pcol][0]/255,PaletteTable[pcol][1]/255,PaletteTable[pcol][2]/255,acol);
		GLfloat PartV[] = {
			p->org[0], p->org[1], p->org[2],
			p->org[0] + up[0]*scale, p->org[1] + up[1]*scale, p->org[2] + up[2]*scale,
			p->org[0] + right[0]*scale, p->org[1] + right[1]*scale, p->org[2] + right[2]*scale
		};
		GLfloat PartT[] = {
			0, 0,
			1, 0,
			0, 1
		};
		glVertexPointer(3, GL_FLOAT, 0, PartV);
		glTexCoordPointer(2, GL_FLOAT, 0, PartT);
		glDrawArrays(GL_TRIANGLE_FAN,0,3);
	
		p->org[0] += p->vel[0]*frametime;
		p->org[1] += p->vel[1]*frametime;
		p->org[2] += p->vel[2]*frametime;
		
		switch (p->type)
		{
		case pt_static:
			break;
		case pt_fire:
			p->ramp += time1;
			if (p->ramp >= 6)
				p->die = -1;
			else
				p->color = ramp3[(int)p->ramp];
			p->vel[2] += grav;
			break;

		case pt_explode:
			p->ramp += time2;
			if (p->ramp >=8)
				p->die = -1;
			else
				p->color = ramp1[(int)p->ramp];
			for (i=0 ; i<3 ; i++)
				p->vel[i] += p->vel[i]*dvel;
			p->vel[2] -= grav;
			break;

		case pt_explode2:
			p->ramp += time3;
			if (p->ramp >=8)
				p->die = -1;
			else
				p->color = ramp2[(int)p->ramp];
			for (i=0 ; i<3 ; i++)
				p->vel[i] -= p->vel[i]*frametime;
			p->vel[2] -= grav;
			break;

		case pt_blob:
			for (i=0 ; i<3 ; i++)
				p->vel[i] += p->vel[i]*dvel;
			p->vel[2] -= grav;
			break;

		case pt_blob2:
			for (i=0 ; i<2 ; i++)
				p->vel[i] -= p->vel[i]*dvel;
			p->vel[2] -= grav;
			break;

		case pt_grav:
#ifdef QUAKE2
			p->vel[2] -= grav * 20;
			break;
#endif
		case pt_slowgrav:
			p->vel[2] -= grav;
			break;
		}

	}

  

  
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glEnd ();
	glDisable (GL_BLEND);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

}

