void print(int inoeud)
{
	int i;
	if(bitmap_inode[inoeud] == 0)
	{
		printf("numéro invalide");
		return;
	}
	inode in = table[inoeud];
	int nbblock = in.numblock[0];
	for ( i = 1;  i<=nbblock; i++)
	{
		int num_block = in.num_bloc[i];
		printf("%s", blocs[num_block]);
	}
}
