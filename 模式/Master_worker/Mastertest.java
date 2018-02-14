package code0212.Master_worker;

import java.util.Random;

/**
 * @Created by  qiao
 * @date 18-2-12 下午5:43
 */

public class Mastertest {

    public static void main(String[] args) {
        Master master=new Master(new Worker(),10);

        Random r=new Random();
        for(int i=0;i<100;i++){
            Task task=new Task();
            task.setId(i);
            task.setName("任务" + i);
            task.setPrice(r.nextInt(1000));
            master.submit(task);
        }
        master.execute();

        long start =System.currentTimeMillis();
        while (true){
            if(master.isComplete()){
                long end =System.currentTimeMillis()-start;
                int ret =master.getResult();
                System.out.println("最终结果是:"+ret+",耗时为:"+end);
                break;
            }
        }
    }


}
