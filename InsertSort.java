package sort;

/**
 * ֱ�Ӳ�������
 * @author shkstart
 * 2013-11-27
 */
public class InsertSort {
	public static void insertSort(DataWrap[] data){
		System.out.println("��ʼ����");
		int arrayLength = data.length;
		for(int i = 1;i < arrayLength;i++){
			DataWrap temp = data[i];
			if(data[i].compareTo(data[i-1]) < 0){
				int j = i -1;
				for(;j >= 0 && data[j].compareTo(temp) > 0;j--){
					data[j +1] = data[j];
				}
				data[j + 1] = temp;
			}
			System.out.println(java.util.Arrays.toString(data));
		}
		
	}
	public static void main(String[] args) {
		DataWrap[] data = { new DataWrap(9, ""), new DataWrap(-16, ""),
				new DataWrap(21, "*"), new DataWrap(23, ""),
				new DataWrap(-30, ""), new DataWrap(-49, ""),
				new DataWrap(21, ""), new DataWrap(30, "*"),
				new DataWrap(30, "")};
		System.out.println("����֮ǰ��\n" + java.util.Arrays.toString(data));
		insertSort(data);
		System.out.println("����֮��\n" + java.util.Arrays.toString(data));
	}
}
