int f(int n) //½×³Ëº¯ÊıÌå
{
	if (n <= 2)
	{
		return n;
	}
	return f(n - 1) * n;
}

