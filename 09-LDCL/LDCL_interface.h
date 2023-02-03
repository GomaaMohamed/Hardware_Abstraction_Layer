/***************************************/
/* Author  :Gomaa                      */
/* Date    :19 Nov 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _LDCL_INTERFACE_H_
#define _LDCL_INTERFACE_H_
/* Load Cell Initialization */
void LDCL_voidInit(void);
/* Read Data from Load Cell........Note: This Function Return 24-bit of Data */
u32 LDCL_u32ReadData(void);



#endif