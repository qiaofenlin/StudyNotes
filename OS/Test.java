package demo;

import java.util.ArrayList;

/**
 * Created by andilyliao on 17-8-19.
 */
class Person{
    private byte idmask=0b100;
    private byte namemask=0b010;
    private byte agemask=0b001;
    private int id;
    private int age;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    private String name;

    public String toString(byte mask) {
        StringBuffer str=new StringBuffer();
        if((this.idmask&mask)!=0){
            str.append("id=" + id+"\t");
        }
        if((this.namemask&mask)!=0){
            str.append("name=" + name+"\t");
        }
        if((this.agemask&mask)!=0){
            str.append("age=" + age+"\t");
        }
        return "Person{" +str +'}';
    }
}
interface Cond{
    boolean isOk(Object o);
}
class Opt{
    private ArrayList list=new ArrayList();
    public void add(Object o){
        this.list.add(o);
    }
    public Opt filter(Cond cond){
        Opt opt=new Opt();
        for (Object o:list){
            if(cond.isOk(o)){
                opt.add(o);
            }
        }
        return opt;
    }
    public void foreach(byte mask){
        for(Object o:this.list){
            System.out.println(((Person)o).toString(mask));
        }
    }
}
public class Test {
    public static void main(String[] args) {
        Opt opt=new Opt();
        for(int i=0;i<100;i++){
            Person p=new Person();
            p.setId(i);
            p.setAge(i);
            p.setName("a"+i);
            opt.add(p);
        }
        opt=opt.filter(new Cond() {
            private boolean flag=false;
            @Override
            public boolean isOk(Object o) {
                if(((Person)o).getAge()>50){
                    flag=true;
                }
                return flag;
            }
        });
        opt.foreach((byte)0b011);

    }
}
