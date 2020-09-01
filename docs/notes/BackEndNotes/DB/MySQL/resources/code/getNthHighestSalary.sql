USE LeetCode;

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N-1;
  RETURN (
      # Write your MySQL query statement below.
      IFNULL(
            (SELECT DISTINCT Salary
            FROM Employee
            ORDER BY Salary DESC
            LIMIT 1 OFFSET N    # 等价于 LIMIT N, 1
            ), NULL)
  );
END;

SELECT getNthHighestSalary(2)
FROM Employee;