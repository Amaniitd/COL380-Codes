#include <mpi.h>
#include <iostream>
using namespace std;

#define INP_SIZE (1 << 20)
#define HRR_SIZE (1 << 20)
#define END (1 << 25)

int BLOCK_LOW(int id, int p) {
	return (id * HRR_SIZE / p);
}

int BLOCK_HIGH(int id, int p) {
	return ((id + 1) * HRR_SIZE / p - 1);
}

int BLOCK_SIZE(int id, int p) {
	return BLOCK_HIGH(id, p) - BLOCK_LOW(id, p) + 1;
}

int BLOCK_OWNER(int index, int p) {
	return (p * index / (HRR_SIZE));
}

void broadcast_end(int id, int p) {
	int buffer = END;
	for (int i = 0; i < p; i++) {
		if (i != id) {
			MPI_Send(&buffer, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
}

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);

	int p, id;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	int from, to, hist_size;
	from = BLOCK_LOW(id, p);
	to = BLOCK_HIGH(id, p);
	hist_size = BLOCK_SIZE(id, p);

	int * hist = (int *) malloc(hist_size * sizeof(int));
	int *inp = (int *) malloc(INP_SIZE * sizeof(int));

	for (int i = 0; i < INP_SIZE; i++) inp[i] = rand() % HRR_SIZE;
	for (int i = 0; i < hist_size; i++) hist[i] = 0;

	int i = 0, buffer, numends = 0, flag = -1, data, owner;
	MPI_Request request;
	MPI_Status status;
	MPI_Irecv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);

	while (i < INP_SIZE || numends < p - 1) {
		//read the datadbase
		if (i < INP_SIZE) {
			data = inp[i]; i++;
			owner = BLOCK_OWNER(data, p);

			if (owner == id) {
				hist[data - from]++;
			}
			else {
				MPI_Request temp;
				MPI_Isend(&data, 1, MPI_INT, owner, 0, MPI_COMM_WORLD, &temp);
			}

			if (i == INP_SIZE) broadcast_end(id, p);
		}

		// update the histogram
		MPI_Test(&request, &flag, & status);

		if (flag == 1) {
			if (buffer != END) {
				hist[buffer % (HRR_SIZE / p)]++;
			}
			else {
				numends++;
			}
			if (numends != p - 1) MPI_Irecv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
		}
	}

	int count = 0;
	for (int i = 0; i < hist_size; i++) count += hist[i];
	cout << "Data stored by processer " << id << " = " << count << endl;

	MPI_Finalize();
}










