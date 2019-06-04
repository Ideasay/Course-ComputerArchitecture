#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define depth_btb 4

int access_2_bht(char last_2_history, char last_history);
int index_of_table(int address, int depth);
int main() {
	/*init bht*/
	char bht[4][64] = { '0' };
	char last_2_history = '0', last_history = '0';
	int addr_1 = 0, addr_2 = 0;
	int access_bht = 0;
	int index_bht = 0;
	int predict_right = 0, predict_wrong = 0;

	/*init btb */
	int btb[depth_btb][2] = { 0 };
	int index_n_btb = 0;
	int hits = 0;
	int jumps = 0;
	int depth = depth_btb;
	
	/*open history.txt*/
	FILE *fp;
	if ((fp = fopen("history.txt", "r")) == NULL) {
		printf("fail to open this file");
		return;
	}

	int branch = 0;
	int record = 0;
	while ((fscanf(fp, "%x	%x	%c", &addr_1, &addr_2, &branch)) == 3) {

		access_bht = access_2_bht(last_2_history, last_history);
		index_bht = index_of_table(addr_1, 64);
		/*predict right*/
		if (bht[access_bht][index_bht] == branch) {
			predict_right++;
		}/*predict wrong*/
		else {
			predict_wrong++;
			bht[access_bht][index_bht] = branch;
		}
		last_2_history = last_history;
		last_history = branch;

		index_n_btb = index_of_table(addr_1, depth_btb);
		if (branch == '1') {
			if (btb[index_n_btb][0] == addr_1) {
				if (btb[index_n_btb][1] == addr_2) {
					hits++;
				}
				else {
					btb[index_n_btb][1] = addr_2;
				}
			}
			else {
				btb[index_n_btb][0] = addr_1;
				btb[index_n_btb][1] = addr_2;
			}
			jumps++;
		}
		record++;
	}
	
	printf("record:%d\nright:%d\nwrong:%d\nmispredict:%.3f%%\n", record, predict_right, predict_wrong, 100 * (float)predict_wrong/(float)record);
	printf("===================================\n");
	printf("depth of btb:%d\nhits_rate:%.3f%%", depth, 100 * (float)hits / (float)jumps);
	fclose(fp);

}

int access_2_bht(char last_2_history, char last_history) {
	if (last_2_history == '0' && last_history == '0') {
		return 0;
	}
	else if (last_2_history == '0' && last_history == '1') {
		return 1;
	}
	else if (last_2_history == '1' && last_history == '0') {
		return 2;
	}
	else if (last_2_history == '1' && last_history == '1') {
		return 3;
	}
}

int index_of_table(int address, int depth) {
	return address % depth;
}

