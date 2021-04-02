namespace vcg {

inline 
void XMLWrite(FILE *fp, const char *label, Matrix44d &Tr)
{
	fprintf(fp,"<Matrix Label=\"%s\"\n",label);
		fprintf(fp,"a00=\"%lf\" a01=\"%lf\" a02=\"%lf \" a03=\"%lf\" \n",(Tr[0][0]),(Tr[0][1]),(Tr[0][2]),(Tr[0][3]));
		fprintf(fp,"a10=\"%lf\" a11=\"%lf\" a12=\"%lf \" a13=\"%lf\" \n",(Tr[1][0]),(Tr[1][1]),(Tr[1][2]),(Tr[1][3]));
		fprintf(fp,"a20=\"%lf\" a21=\"%lf\" a22=\"%lf \" a23=\"%lf\" \n",(Tr[2][0]),(Tr[2][1]),(Tr[2][2]),(Tr[2][3]));
		fprintf(fp,"a30=\"%lf\" a31=\"%lf\" a32=\"%lf \" a33=\"%lf\" \n",(Tr[3][0]),(Tr[3][1]),(Tr[3][2]),(Tr[3][3]));
	fprintf(fp,"/>\n");
}

inline 
void XMLRead(Xml &xml,const char *label,Matrix44d &Tr)
{
	if(xml["Label"]!=string(label)) {
		TRACE("Error in xmlMatrixRead, expected label '%s', but found '%s'\n",label,xml["Label"]);
		return;
	}
	Tr[0][0]=atof(xml["a00"].c_str());	Tr[0][1]=atof(xml["a01"].c_str());	Tr[0][2]=atof(xml["a02"].c_str());	Tr[0][3]=atof(xml["a03"].c_str());
	Tr[1][0]=atof(xml["a10"].c_str());	Tr[1][1]=atof(xml["a11"].c_str());	Tr[1][2]=atof(xml["a12"].c_str());	Tr[1][3]=atof(xml["a13"].c_str());
	Tr[2][0]=atof(xml["a20"].c_str());	Tr[2][1]=atof(xml["a21"].c_str());	Tr[2][2]=atof(xml["a22"].c_str());	Tr[2][3]=atof(xml["a23"].c_str());
	Tr[3][0]=atof(xml["a30"].c_str());	Tr[3][1]=atof(xml["a31"].c_str());	Tr[3][2]=atof(xml["a32"].c_str());	Tr[3][3]=atof(xml["a33"].c_str());
}

inline 
void XMLWrite(FILE *fp, const char *label, Matrix44f &Tr)
{
	fprintf(fp,"<Matrix Label=\"%s\"\n",label);
		fprintf(fp,"a00=\"%lf\" a01=\"%lf\" a02=\"%lf \" a03=\"%lf\" \n",(Tr[0][0]),(Tr[0][1]),(Tr[0][2]),(Tr[0][3]));
		fprintf(fp,"a10=\"%lf\" a11=\"%lf\" a12=\"%lf \" a13=\"%lf\" \n",(Tr[1][0]),(Tr[1][1]),(Tr[1][2]),(Tr[1][3]));
		fprintf(fp,"a20=\"%lf\" a21=\"%lf\" a22=\"%lf \" a23=\"%lf\" \n",(Tr[2][0]),(Tr[2][1]),(Tr[2][2]),(Tr[2][3]));
		fprintf(fp,"a30=\"%lf\" a31=\"%lf\" a32=\"%lf \" a33=\"%lf\" \n",(Tr[3][0]),(Tr[3][1]),(Tr[3][2]),(Tr[3][3]));
	fprintf(fp,"/>\n");
}

inline 
void XMLRead(Xml &xml,const char *label,Matrix44f &Tr)
{
	if(xml["Label"]!=string(label)) {
		TRACE("Error in xmlMatrixRead, expected label '%s', but found '%s'\n",label,xml["Label"]);
		return;
	}
	Tr[0][0]=(float)atof(xml["a00"].c_str());	Tr[0][1]=(float)atof(xml["a01"].c_str());	Tr[0][2]=(float)atof(xml["a02"].c_str());	Tr[0][3]=(float)atof(xml["a03"].c_str());
	Tr[1][0]=(float)atof(xml["a10"].c_str());	Tr[1][1]=(float)atof(xml["a11"].c_str());	Tr[1][2]=(float)atof(xml["a12"].c_str());	Tr[1][3]=(float)atof(xml["a13"].c_str());
	Tr[2][0]=(float)atof(xml["a20"].c_str());	Tr[2][1]=(float)atof(xml["a21"].c_str());	Tr[2][2]=(float)atof(xml["a22"].c_str());	Tr[2][3]=(float)atof(xml["a23"].c_str());
	Tr[3][0]=(float)atof(xml["a30"].c_str());	Tr[3][1]=(float)atof(xml["a31"].c_str());	Tr[3][2]=(float)atof(xml["a32"].c_str());	Tr[3][3]=(float)atof(xml["a33"].c_str());
}
}