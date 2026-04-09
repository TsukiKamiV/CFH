# Article

<!--@START_MENU_TOKEN@-->Summary<!--@END_MENU_TOKEN@-->

## Overview

<!--@START_MENU_TOKEN@-->Text<!--@END_MENU_TOKEN@-->

### Section header

<!--@START_MENU_TOKEN@-->Text<!--@END_MENU_TOKEN@-->
/**
 *@brief	 CPP09要求：每个exercise必须使用至少一个container，且前面题目使用过的container，后续题目里不允许再次使用
 *选择container的标准基于题目规定的数据之间的关系和处理目的，即最大限度把数据约束交给container，利用其自身特性，而不是交给业务代码管理
 *题目要求按照 “date | value"形式储存数据，符合 "key - value"关系，更适用于std::map container
 *	-key本身就是身份，value则没有意义，除非通过key被访问 —— 这是“按身份访问数据”的典型模式（而不是通过下标/顺序遍历扫描）
 *	⭐️std::map的性质：
 *	Collection of key-value pairs sorted on the basis of the keys where no two pairs have same keys.
 *因此本题选择map的原因可以归纳为：
 	“因为我的数据天然是 key–value 结构，
 	核心操作是按 key 定位而不是遍历；
 	同时 key 本身有顺序语义，容器内部自动维护有序性和唯一性，
 	这正是我需要的行为模型，用顺序容器反而会削弱语义。”
 */

/**
 * map 的性质：
 * 1️⃣ key–value，而不是 index–value
 	•	map 没有下标语义
 	•	数据只能通过 key 访问
 * 2️⃣ 自动有序（by key）
 * 	•	插入顺序 不重要
 	•	内部始终按 key 的 '<'关系排序
	•	排序规则默认使用 operator<
 * 3️⃣ key 唯一（强约束）
	•	同一个 key 只能存在一次
	•	再次插入相同 key：
	•	要么失败
	•	要么覆盖（取决于用法
 */
