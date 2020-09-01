use learnDB;

# 一个返回产品平均价格的存储过程。
delimiter $

create procedure productpricing()
begin
    select avg(prod_price) as priceavg
    from products;
end $

delimiter;