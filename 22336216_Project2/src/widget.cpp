#include "widget.h"
#include "./ui_widget.h"
#include <stack>
#include <math.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString s;
    s.clear();
    bool correct=true;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_eql_clicked()
{
    int begin=0;
    s=ui->lineEdit->text();
    double result=calculate(s,begin);
    if(correct==false){
        ui->lineEdit_2->setText("ERROR");
        return;
    }
    ui->lineEdit_2->setText("");
    ui->lcdNumber->display(result);
}

void Widget::on_pushButton_0_clicked()
{
    s+="0";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_1_clicked()
{
    s+="1";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_2_clicked()
{
    s+="2";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_3_clicked()
{
    s+="3";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_4_clicked()
{
    s+="4";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_5_clicked()
{
    s+="5";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_6_clicked()
{
    s+="6";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_7_clicked()
{
    s+="7";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_8_clicked()
{
    s+="8";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_9_clicked()
{
    s+="9";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_add_clicked()
{
    s+="+";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_back_clicked()
{
    s=s.left(s.size()-1);
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_clear_clicked()
{
    s.clear();
    correct=true;
    ui->lineEdit->setText(s);
    ui->lineEdit_2->setText(s);
    ui->lcdNumber->display(0);
}

void Widget::on_pushButton_div_clicked()
{
    s+="/";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_mul_clicked()
{
    s+="*";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_pow_clicked()
{
    s+="^";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_sub_clicked()
{
    s+="-";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_left_clicked()
{
    s+="(";
    ui->lineEdit->setText(s);
}

void Widget::on_pushButton_right_clicked()
{
    s+=")";
    ui->lineEdit->setText(s);
}

double Widget::calculate(QString str,int &i){
    char operation = '+';
    std::string s=str.toStdString();
    std::stack<double> nums;
    double num = 0.00;
    double res = 0.00;
    correct=true;
    for (i; i < s.size(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 10 + (s[i] - '0');
        }
        if (s[i] == '(')
        {
            num = calculate(str, ++i); //从i的下一个开始计算， 进入递归
            i++; //计算完之后的i指向)所以再++
        }
        if (((s[i] < '0' || s[i] > '9') && s[i] != ' ') || i >= s.size() - 1) // 继续计算
        {
            double pre = 0.00;
            switch (operation)
            {
            case '+': nums.push(num);
                break;
            case '-': nums.push(-num);
                break;
            case '*':
                pre = nums.top();
                nums.pop();
                nums.push(pre * num);
                break;
            case '/':
                pre = nums.top();
                nums.pop();
                if(num==0){
                    correct=false;
                    nums.push(-1);
                }
                else nums.push(pre / num);
                break;
            case '^':
                pre = nums.top();
                nums.pop();
                nums.push(pow(pre,num));
                break;
            }

            operation = s[i];
            num = 0.00;
        }
        if (s[i] == ')') //遇到)回到上一级递归
        {
            break;
        }
    }
    while (!nums.empty())
    {
        res += nums.top();
        nums.pop();
    }
    return res;
}

void Widget::on_pushButton_point_clicked()
{
    s+=".";
    ui->lineEdit->setText(s);
}

