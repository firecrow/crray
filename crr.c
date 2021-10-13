 /*
 * Copyright 2020-2021 Firecrow Silvernight
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define min(x,y) (((x) < (y)) ? (x) : (y))
#define max(x,y) (((x) > (y)) ? (x) : (y))

struct crr {
    int allocated;
    int length;
    char *data;
};

struct crrptr {
    int allocated;
    int length;
    void **data;
};

struct crrptr *crrptr_alloc(){
    struct crrptr *r = malloc(sizeof(struct crrptr));
    if(!r) exit(123);
    bzero(r, sizeof(struct crrptr));
    r->data = malloc(16*sizeof(void *));
    r->allocated = 16;
    return r;
}

int crrptr_insert(struct crrptr *r, void *data, int idx){
    void **idxptr;
    int needed = r->length+1; 
    if(needed > r->allocated){
        size_t newsize = r->allocated*sizeof(void *);
        size_t needed_size = needed*sizeof(void *);
        while(newsize < needed_size){
            newsize *= 2;
        }
        r->data = realloc(r->data, newsize);
        if(!r->data) exit(123);
    }
    if(idx == -1 || (idx >= r->length)){
        idxptr = r->data+r->length;
    }else{
        idxptr = r->data+idx;
        memmove(idxptr+1, idxptr, (r->length - idx)*sizeof(void *));
    }
    memcpy(idxptr, &data, sizeof(void *));
    r->length++;
}

void *crrptr_pop(struct crrptr *r, int idx){
    void *optr;
    if(idx > r->length-1){
        return NULL;
    }
    if(idx == -1){
        optr = *(r->data+(r->length-1));
        r->length--;
        return optr;
    }else{
        void **idxptr = r->data+idx;
        optr = *(idxptr);
        memmove(idxptr, idxptr+1, (r->length - idx)*sizeof(void *));
        r->length--;
        return optr;
    }
}

void *crrptr_get(struct crrptr *r, int idx){
    if(idx > r->length-1){
        return NULL;
    }
    return *(r->data+idx);
}

/* only for debugging purposes on character data */
void crrptr_print(struct crrptr *c){
    int i;
    for(i=0; i<c->length; i++){
        printf("%d: %s\n", i, (char *)c->data[i]);
    }
}

struct crr *crr_alloc(){
    struct crr *r = malloc(sizeof(struct crr)+1);
    if(!r) exit(123);
    bzero(r, sizeof(struct crr));
    r->data = malloc(16);
    r->data[0] = '\0';
    r->allocated = 16;
    return r;
}

int crr_push(struct crr *r, char *data, int length){
    int needed = r->length+length; 
    if(needed > r->allocated){
        int newsize = r->allocated;
        while(newsize < needed){
            newsize *= 2;
        }
        r->data = realloc(r->data, newsize+1);
        if(!r->data) exit(123);
    }
    memcpy(r->data+r->length, data, length);
    r->length += length;
    r->data[r->length] = '\0';
}

int crr_shift(struct crr *r, int count){
    memmove(r->data, r->data+count, r->length-count);
    r->length -= count;
    r->data[r->length] = '\0';
}

struct crr *crr_alloc_with_cstr(char *cstr){
    struct crr *r = crr_alloc();
    crr_push(r, cstr, strlen(cstr));
    return r;
}

int crr_cmp(struct crr *a, struct crr *b){
    return strncmp(a->data, b->data, max(a->length, b->length));
}

int crr_cmp_cstr(struct crr *a, char *b){
    return strncmp(a->data, b, max(a->length, strlen(b)));
}

void crr_lines_from_fd(int fd, struct read_progress *progress, struct crr *(*process)(struct crr *crr)){
    struct read_progress *p = progress;
    char c;
    int i;
    struct crr *new;
    while(1){
        /*
        while(1){
            len = read(fd, &(p->buff), FCLFPLAY_BUFF_SIZE); 
            p->seglen = 0;
            c = &(p->buff);
            i = 0;
            while(i++ < p->len && *c++ != '\n')
                p->seglen++;
            crr_push(p->crr, &(p->buff), p->seglen);
        }
        */
        if(p->seglen != p->len){
            if(process){
                new = process(p->crr);
                if(new){
                    p->crr = new;
                }
            }
            crrptr_insert(p->cptr, p->crr, -1); 
            p->crr = crr_alloc();
            crr_push(p->crr, p->buff+p->seglen, p->len-p->seglen);
        }
    }
}

void crr_free(struct crr *r){
    free(r->data);
    free(r);
}

