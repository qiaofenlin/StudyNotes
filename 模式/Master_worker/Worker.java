package code0212.Master_worker;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue; /**
 * @Created by  qiao
 * @date 18-2-12 下午5:18
 */

public class Worker implements Runnable{
    private ConcurrentLinkedQueue<Task> workplace;
    private ConcurrentHashMap<String, Object> resuleMap;


    public void setWorkQueue(ConcurrentLinkedQueue<Task> workplace) {
        this.workplace=workplace;
    }

    public void setResultMap(ConcurrentHashMap<String, Object> resuleMap) {
        this.resuleMap=resuleMap;
    }

    private Object handle(Task input) {
        Object output=null;
        try {
            Thread.sleep(1000);
            output =input.getPrice();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return output;


    }

    @Override
    public void run() {
        while (true){
            Task input = this.workplace.poll();
            if(input==null){
                break;
            }
            Object output=handle(input);
            this.resuleMap.put(Integer.toString(input.getId()),output);

        }

    }


}
