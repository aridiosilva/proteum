/* Copyright (C) 2012 -- Marcio Eduardo Delamaro and Jose Carlos Maldonado
# 
# 
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
# 
*/


#include        <lib/gerais.h>
#include        <muta/lib/muta.h>
#include        <polonesa/polonesa.h>
#include        <li/lib/li.h>
#include        "opmuta.h"

extern int     Seq[];

extern	OPERADOR_MUTACAO g_tab_operador[]; 

extern  LI_SIMBOLO      sym;    /* simbolo 'lido' */

extern  char    bufmen[];       /* buffer auxiliar global */

extern  EXPRE_POS       expre_pos,
                        ex_aux;

static	Operador;

int	nbreak;

LI_SIMBOLO	bvet[100];

char *label_muta();


init_sbrn(int x)
{
   bvet[nbreak] = sym;
   bvet[nbreak++].linha = x;
}


u_sbrn(int nivel, LI_SIMBOLO *si)
{
int     i, u, t, max, seq, nseq;
char    *q, *get_rand();
OSET    *p, *monta_pset();

   Operador = U_SBRn;
   if (g_tab_operador[Operador].percentage == 0.0)
        return;
   max = g_tab_operador[Operador].maximum;
   if (max == 0) max--;

   u = sym.no;
   ex_aux = expre_pos;
   p = monta_pset(nbreak);
   nseq = nbreak;

   for (q = get_rand(p, Operador); 
	max != 0 && q != NULL; q = get_rand(p, Operador), max--)
   {
	seq = i = atoi(q);
	if ( bvet[i].linha - nivel < 2)
	{
	   max++;
	   continue;
	}
        add_descritor(si->inicio, 0, si->no, "{");
	sprintf(bufmen, "BREAK_OUT_TO_N_LEVEL(%s); ", label_muta());
        add_descritor(bvet[i].inicio, bvet[i].comprimento, bvet[i].no, bufmen);
	sprintf(bufmen, "if (0) %s: break; }", label_muta());
        add_descritor(sym.inicio, 0, u, bufmen);
        sorteia_grupoU(Operador, Seq[Operador]+seq);
   }
   set_free(p);
   Seq[Operador] += nseq;
}

