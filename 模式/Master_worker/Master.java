package code0212.Master_worker;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * @Created by  qiao
 * @date 18-2-12 下午5:18
 */

public class Master {
    private ConcurrentLinkedQueue<Task> workplace =new ConcurrentLinkedQueue<Task>();

    private HashMap<String,Thread> workers =new HashMap<String, Thread>();

    private ConcurrentHashMap<String,Object> resuleMap =new ConcurrentHashMap<>();

    public Master(Worker worker,int workCount){
        worker.setWorkQueue(this.workplace);
        worker.setResultMap(this.resuleMap);

        for(int i=0;i<workCount;i++){
            workers.put("字节点"+Integer.toString(i),new Thread(worker));
        }
    }

    public void submit(Task task){
        this.workplace.add(task);
    }

    public void execute(){
        for (Map.Entry<String ,Thread> me :workers.entrySet()){
            me.getValue().start();

        }

    }

    //判断是否完成.
    public boolean isComplete() {
        for (Map.Entry<String ,Thread> me :workers.entrySet()){
            if(me.getValue().getState()!=Thread.State.TERMINATED)
                return false;
        }
        return true;
    }

    //总结归纳
    public int getResult() {
        int ret=0;
        for (Map.Entry<String ,Object> me :resuleMap.entrySet()){
            ret+=(Integer) me.getValue();
        }
        return 0;
    }
}
