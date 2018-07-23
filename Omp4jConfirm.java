public class Omp4jConfirm
{
	
	public static void main(String[] args) 
	{
		// omp parallel threadNum(2)
		{
			int a = OMP4J_THREAD_NUM;
			// omp critical
			{
				System.out.printf("hi from thread %d\n", a);
			}
		}
	}
}