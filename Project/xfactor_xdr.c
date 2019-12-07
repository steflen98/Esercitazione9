/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "xfactor.h"

bool_t
xdr_Candidato (XDR *xdrs, Candidato *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nome, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->giudice, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->categoria))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->nomefile, 256,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->fase))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->voto))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Candidati (XDR *xdrs, Candidati *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->candidato, NUMCANDIDATI,
		sizeof (Candidato), (xdrproc_t) xdr_Candidato))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Giudice (XDR *xdrs, Giudice *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nome, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->punteggio))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Giudici (XDR *xdrs, Giudici *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->giudice, NUMGIUDICI,
		sizeof (Giudice), (xdrproc_t) xdr_Giudice))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Input (XDR *xdrs, Input *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nome, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operazione))
		 return FALSE;
	return TRUE;
}
