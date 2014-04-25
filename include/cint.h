/*
 * File: cint.h
 * Author: Qiming Sun <osirpt.sun@gmail.com>
 *
 * Parameters and function prototypes for libcint.
 */

#define PTR_LIGHT_SPEED         0
#define PTR_COMMON_ORIG         1
#define PTR_SHIELDING_ORIG      4
#define PTR_RINV_ORIG           4
#define PTR_AO_GAUGE            7
#define PTR_ENV_START           20

// slots of atm
#define CHARGE_OF       0
#define PTR_COORD       1
#define NUC_MOD_OF      2
#define PTR_MASS        3
#define RAD_GRIDS       4
#define ANG_GRIDS       5
#define ATM_SLOTS       6


// slots of bas
#define ATOM_OF         0
#define ANG_OF          1
#define NPRIM_OF        2
#define NCTR_OF         3
#define KAPPA_OF        4
#define PTR_EXP         5
#define PTR_COEFF       6
#define RESERVE_BASLOT  7
#define BAS_SLOTS       8

// slots of gout
#define POSX            0
#define POSY            1
#define POSZ            2
#define POS1            3
#define POSXX           0
#define POSYX           1
#define POSZX           2
#define POS1X           3
#define POSXY           4
#define POSYY           5
#define POSZY           6
#define POS1Y           7
#define POSXZ           8
#define POSYZ           9
#define POSZZ           10
#define POS1Z           11
#define POSX1           12
#define POSY1           13
#define POSZ1           14
#define POS11           15

// tensor
#define TSRX        0
#define TSRY        1
#define TSRZ        2
#define TSRXX       0
#define TSRXY       1
#define TSRXZ       2
#define TSRYX       3
#define TSRYY       4
#define TSRYZ       5
#define TSRZX       6
#define TSRZY       7
#define TSRZZ       8

// some other boundary
#define ANG_MAX         6 // l = 0..5
#define OF_CMPLX        2
#define POINT_NUC       1
#define GAUSSIAN_NUC    2

#define bas(SLOT,I)     bas[BAS_SLOTS * (I) + (SLOT)]
#define atm(SLOT,I)     atm[ATM_SLOTS * (I) + (SLOT)]

#if !defined HAVE_DEFINED_CINTOPT_H
#define HAVE_DEFINED_CINTOPT_H
typedef struct {
    unsigned int **index_xyz_array; // ANG_MAX**4 pointers to index_xyz
    unsigned int *prim_offset;
    unsigned int *non0ctr;
    unsigned int **non0idx;
    double **non0coeff;
    double **expij;
    double **rij;
    int **cceij;
    unsigned int tot_prim;
} CINTOpt;
#endif

unsigned int CINTlen_cart(const unsigned int l);
unsigned int CINTlen_spinor(const unsigned int bas_id, const int *bas);

unsigned int CINTcgtos_cart(const unsigned int bas_id, const int *bas);
unsigned int CINTcgtos_spheric(const unsigned int bas_id, const int *bas);
unsigned int CINTcgtos_spinor(const unsigned int bas_id, const int *bas);

unsigned int CINTtot_pgto_spheric(const int *bas, const int nbas);
unsigned int CINTtot_pgto_spinor(const int *bas, const int nbas);

unsigned int CINTtot_cgto_cart(const int *bas, const int nbas);
unsigned int CINTtot_cgto_spheric(const int *bas, const int nbas);
unsigned int CINTtot_cgto_spinor(const int *bas, const int nbas);

void CINTshells_cart_offset(int ao_loc[], const int *bas, const int nbas);
void CINTshells_spheric_offset(int ao_loc[], const int *bas, const int nbas);
void CINTshells_spinor_offset(int ao_loc[], const int *bas, const int nbas);


double CINTgto_norm(int n, double a);


void CINTinit_2e_optimizer(CINTOpt **opt, const int *atm, const int natm,
                           const int *bas, const int nbas, const double *env);
void CINTinit_optimizer(CINTOpt **opt, const int *atm, const int natm,
                        const int *bas, const int nbas, const double *env);
void CINTdel_2e_optimizer(CINTOpt **opt);
void CINTdel_optimizer(CINTOpt **opt);


int cint2e_cart(double *opijkl, const unsigned int *shls,
                const int *atm, const int natm,
                const int *bas, const int nbas, const double *env,
                const CINTOpt *opt);
void cint2e_cart_optimizer(CINTOpt **opt, const int *atm, const int natm,
                           const int *bas, const int nbas, const double *env);
int cint2e_sph(double *opijkl, const unsigned int *shls,
               const int *atm, const int natm,
               const int *bas, const int nbas, const double *env,
               const CINTOpt *opt);
void cint2e_sph_optimizer(CINTOpt **opt, const int *atm, const int natm,
                          const int *bas, const int nbas, const double *env);
int cint2e(double *opijkl, const unsigned int *shls,
           const int *atm, const int natm,
           const int *bas, const int nbas, const double *env,
           const CINTOpt *opt);
void cint2e_optimizer(CINTOpt **opt, const int *atm, const int natm,
                      const int *bas, const int nbas, const double *env);
